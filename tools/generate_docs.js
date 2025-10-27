const fs = require("fs");
const readline = require("node:readline");
const path = require("path");

const TYPE_MAPPINGS = {
  "StringCharPtr": "const char*",
  "objectPtr": "void*",
  "voidPtr": "void*",
  "OutputStringViewPtr": "CAPIStringView*",
  "OutputStringBufferPtr": "CAPIStringBuffer*"
};

const CAPI_DIR = "../../Server/Components/CAPI/Impl";
const OUTPUT_FILE = "../apidocs/api.json";
const API_PREFIX = "OMP_CAPI(";

function convertTypeName(type) {
  return TYPE_MAPPINGS[type] || type;
}

function parseParameter(paramString) {
  const parts = paramString.trim().split(" ");
  if (parts.length < 2) return undefined;

  return {
    name: parts[1],
    type: convertTypeName(parts[0])
  };
}

function parseAPILine(line) {
  const content = line.replace(API_PREFIX, "");
  const [apiName, rest] = content.split(", ");
  const componentName = apiName.split("_")[0];

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
    component: componentName,
    api: {
      ret: convertTypeName(returnType),
      name: apiName,
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

async function getAllAPIFiles() {
  return fs
    .readdirSync(CAPI_DIR, { recursive: true })
    .filter(file => file.endsWith("APIs.cpp"))
    .map(file => path.join(CAPI_DIR, file));
}

async function buildAPIDocumentation() {
  const apiFiles = await getAllAPIFiles();
  const apisByComponent = {};

  for (const filePath of apiFiles) {
    const apis = await processFile(filePath);

    for (const { component, api } of apis) {
      if (!apisByComponent[component]) {
        apisByComponent[component] = [];
      }
      apisByComponent[component].push(api);
    }
  }

  return apisByComponent;
}

async function main() {
  try {
    const documentation = await buildAPIDocumentation();
    fs.writeFileSync(OUTPUT_FILE, JSON.stringify(documentation, null, 2));
    console.log(`API documentation generated at ${OUTPUT_FILE}`);
  } catch (error) {
    console.error("Error generating API documentation:", error);
    process.exit(1);
  }
}

main();
