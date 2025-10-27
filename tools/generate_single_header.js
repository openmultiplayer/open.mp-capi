const fs = require("fs");
const readline = require("node:readline");
const path = require("path");

const OUTPUT_FILE = "../include/ompcapi.h";
const CAPI_DIR = "../../Server/Components/CAPI/Impl";
const EVENTS_FILE = "../apidocs/events.json";
const API_PREFIX = "OMP_CAPI(";

const ENTITY_TYPES = [
  "Player", "Vehicle", "Menu", "TextDraw", "TextLabel", "Object",
  "PlayerObject", "PlayerTextLabel3D", "PlayerTextDraw", "Class",
  "GangZone", "Pickup", "NPC"
];

const TYPE_MAPPINGS = {
  function: {
    "StringCharPtr": "const char*",
    "objectPtr": "void*",
    "voidPtr": "void*",
    "OutputStringViewPtr": "struct CAPIStringView*",
    "OutputStringBufferPtr": "struct CAPIStringBuffer*",
    "ComponentVersion": "struct ComponentVersion"
  },
  event: {
    "CAPIStringView": "struct CAPIStringView"
  }
};

const HEADER_TEMPLATE = `#ifndef OMPCAPI_H
#define OMPCAPI_H

#include <stdint.h>
#include <stdbool.h>

#ifndef CAPI_COMPONENT_BUILD
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <Windows.h>
#define LIBRARY_OPEN(path) LoadLibrary(path)
#define LIBRARY_GET_ADDR(lib, symbol) GetProcAddress((HMODULE)lib, symbol)
#else
#include <dlfcn.h>
#define LIBRARY_OPEN(path) dlopen(path, RTLD_LAZY | RTLD_LOCAL)
#define LIBRARY_GET_ADDR dlsym
#endif
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define OMP_API_EXPORT __declspec(dllexport)
#else
#define OMP_API_EXPORT __attribute__((visibility("default")))
#endif

// Events

enum EventPriorityType
{
	EventPriorityType_Highest,
	EventPriorityType_FairlyHigh,
	EventPriorityType_Default,
	EventPriorityType_FairlyLow,
	EventPriorityType_Lowest,
};

struct EventArgs_Common
{
	int size;
	void** list;
};

typedef bool (*EventCallback_Common)(struct EventArgs_Common* args);

// Components

struct ComponentVersion
{
	uint8_t major; ///< MAJOR version when you make incompatible API changes
	uint8_t minor; ///< MINOR version when you add functionality in a backwards compatible manner
	uint8_t patch; ///< PATCH version when you make backwards compatible bug fixes
	uint16_t prerel; ///< PRE-RELEASE version
};

typedef void (*ComponentOnReadyCallback)();
typedef void (*ComponentOnResetCallback)();
typedef void (*ComponentOnFreeCallback)();

/* Borrowed, read-only view. Callee does NOT copy or allocate.
   Lifetime is tied to the source that produced it. */
struct CAPIStringView
{
	unsigned int len; /* string length */
	const char* data; /* may not be NUL-terminated */
};

/* Caller-provided, writable buffer. Callee copies into this.
   'capacity' is total space available in 'data'. Callee sets 'len' written. */
struct CAPIStringBuffer
{
	unsigned int capacity; /* bytes available in 'data' */
	unsigned int len; /* bytes actually written (out) */
	char* data; /* writable buffer supplied by the caller */
};

#ifndef CAPI_COMPONENT_BUILD

`;

function convertFunctionArgType(type) {
  return TYPE_MAPPINGS.function[type] || type;
}

function convertEventArgType(type) {
  return TYPE_MAPPINGS.event[type] || type;
}

function parseParameter(paramString) {
  const parts = paramString.trim().split(" ");
  if (parts.length < 2) return undefined;

  return {
    name: parts[1],
    type: convertFunctionArgType(parts[0])
  };
}

function parseAPILine(line) {
  const content = line.replace(API_PREFIX, "");
  const [fullName, rest] = content.split(", ");
  const [group, ...nameParts] = fullName.split("_");
  const name = nameParts.join("_");

  const returnTypeEnd = rest.indexOf("(");
  const returnType = rest.substring(0, returnTypeEnd);

  const paramsStart = content.indexOf("(", content.indexOf(returnType)) + 1;
  const paramsEnd = content.indexOf(")");
  const paramsString = content.substring(paramsStart, paramsEnd);

  const parameters = paramsString
    .split(", ")
    .map(parseParameter)
    .filter(Boolean);

  return {
    group,
    api: {
      ret: convertFunctionArgType(returnType),
      name,
      params: parameters
    }
  };
}

async function processFile(filePath) {
  const apis = [];
  const fileStream = fs.createReadStream(filePath);
  const rl = readline.createInterface({
    input: fileStream,
    crlfDelay: Infinity
  });

  for await (const line of rl) {
    if (line.startsWith(API_PREFIX)) {
      apis.push(parseAPILine(line));
    }
  }

  return apis;
}

async function collectAPIs() {
  const files = fs
    .readdirSync(CAPI_DIR, { recursive: true })
    .filter(file => file.endsWith("APIs.cpp"));

  const apisByGroup = {};

  for (const file of files) {
    const filePath = path.join(CAPI_DIR, file);
    const apis = await processFile(filePath);

    for (const { group, api } of apis) {
      if (!apisByGroup[group]) {
        apisByGroup[group] = [];
      }
      apisByGroup[group].push(api);
    }
  }

  return apisByGroup;
}

function writeEntityTypeDefinitions() {
  const definitions = ENTITY_TYPES
    .map(type => `typedef void* ${type};\n`)
    .join("");
  fs.appendFileSync(OUTPUT_FILE, definitions);
}

function writeFunctionTypeDefinitions(apis) {
  Object.entries(apis).forEach(([group, functions]) => {
    fs.appendFileSync(OUTPUT_FILE, `\n\n// ${group} function type definitions\n`);

    functions.forEach(func => {
      const params = func.params
        .map(param => `${param.type} ${param.name}`)
        .join(", ");
      fs.appendFileSync(
        OUTPUT_FILE,
        `typedef ${func.ret} (*${group}_${func.name}_t)(${params});\n`
      );
    });
  });
}

function writeEventDefinitions(events) {
  Object.entries(events).forEach(([group, eventList]) => {
    fs.appendFileSync(
      OUTPUT_FILE,
      `\n\n// ${group} event type and arguments definitions`
    );

    eventList.forEach(event => {
      const args = event.args
        .map(param => `        ${convertEventArgType(param.type)}* ${param.name};`)
        .join("\n");

      fs.appendFileSync(OUTPUT_FILE, `
struct EventArgs_${event.name} {
    int size;
    struct {
${args}
    } *list;
};
typedef bool (*EventCallback_${event.name})(struct EventArgs_${event.name} args);\n`);
    });
  });

  fs.appendFileSync(OUTPUT_FILE, `\n`);
}

function writeStructDefinitions(apis) {
  Object.entries(apis).forEach(([group, functions]) => {
    fs.appendFileSync(OUTPUT_FILE, `\n// ${group} functions\nstruct ${group}_t {\n`);

    functions.forEach(func => {
      fs.appendFileSync(OUTPUT_FILE, `    ${group}_${func.name}_t ${func.name};\n`);
    });

    fs.appendFileSync(OUTPUT_FILE, `};\n`);
  });
}

function writeMainAPIStruct(apis) {
  fs.appendFileSync(OUTPUT_FILE, `\n// All APIs\nstruct OMPAPI_t {\n`);

  Object.keys(apis).forEach(group => {
    fs.appendFileSync(OUTPUT_FILE, `    struct ${group}_t ${group};\n`);
  });

  fs.appendFileSync(OUTPUT_FILE, `};\n`);
}

function writeInitializationFunction(apis) {
  fs.appendFileSync(OUTPUT_FILE, `
static bool omp_initialize_capi(struct OMPAPI_t* ompapi) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    void* capi_lib = LIBRARY_OPEN("./components/$CAPI.dll");
#else
    void* capi_lib = LIBRARY_OPEN("./components/$CAPI.so");
#endif

    // Check if library was loaded successfully
    if (!capi_lib)
    {
        return false;
    }

    // Verify one of the core C apis is available
    ompapi->Core.TickCount = (Core_TickCount_t)LIBRARY_GET_ADDR(capi_lib, "Core_TickCount");

    if (!ompapi->Core.TickCount)
    {
        return false;
    }
`);

  Object.entries(apis).forEach(([group, functions]) => {
    fs.appendFileSync(OUTPUT_FILE, `\n    // Retrieve ${group} functions\n`);

    functions.forEach(func => {
      fs.appendFileSync(
        OUTPUT_FILE,
        `    ompapi->${group}.${func.name} = (${group}_${func.name}_t)LIBRARY_GET_ADDR(capi_lib, "${group}_${func.name}");\n`
      );
    });
  });

  fs.appendFileSync(OUTPUT_FILE, `\n    return true;\n};\n`);
}

function writeFooter() {
  fs.appendFileSync(OUTPUT_FILE, `\n#endif\n\n#endif /* OMPCAPI_H */\n`);
}

async function generateHeader() {
  try {
    fs.writeFileSync(OUTPUT_FILE, HEADER_TEMPLATE);

    writeEntityTypeDefinitions();

    const apis = await collectAPIs();
    const events = require(EVENTS_FILE);

    writeFunctionTypeDefinitions(apis);
    writeEventDefinitions(events);
    writeStructDefinitions(apis);
    writeMainAPIStruct(apis);
    writeInitializationFunction(apis);
    writeFooter();

    console.log(`Header file generated at ${OUTPUT_FILE}`);
  } catch (error) {
    console.error("Error generating header file:", error);
    process.exit(1);
  }
}

generateHeader();
