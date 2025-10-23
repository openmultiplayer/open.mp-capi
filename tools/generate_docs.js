const fs = require("fs");
const readline = require("node:readline");

const files = fs
  .readdirSync("../../Server/Components/CAPI/Impl", { recursive: true })
  .filter((file) => {
    return file.endsWith("APIs.cpp");
  });

const APIs = {};

const convertTypeNames = (type) => {
  if (type === "StringCharPtr") {
    return "const char*";
  } else if (type === "objectPtr") {
    return "void*";
  } else if (type === "voidPtr") {
    return "void*";
  } else if (type === "OutputStringViewPtr") {
    return "CAPIStringView*";
  }
  else if (type === "OutputStringBufferPtr") {
    return "CAPIStringBuffer*";
  } else {
    return type;
  }
};

files.forEach(async (file, index) => {
  const data = fs.createReadStream("../../Server/Components/CAPI/Impl/" + file);
  const lines = readline.createInterface({
    input: data,
    crlfDelay: Infinity,
  });

  for await (const line of lines) {
    if (line.startsWith("OMP_CAPI(")) {
      const v0 = line.replace("OMP_CAPI(", "");
      const name = v0.split(", ")[0];
      const component = name.split("_")[0];

      if (APIs[component] === undefined) {
        APIs[component] = [];
      }

      const v1 = v0.split(", ")[1];
      const ret = v1.substring(0, v1.indexOf("("));
      const v2 = v0.replace(`OMP_CAPI(${name}, ${ret}`, "");
      const params = v2
        .substring(v2.indexOf("(") + 1, v2.indexOf(")"))
        .split(", ")
        .map((param) => {
          const name = param.split(" ")[1];
          const type = param.split(" ")[0];

          if (name === undefined) {
            return undefined;
          }

          return {
            name,
            type: convertTypeNames(type),
          };
        });

      APIs[component].push({
        ret: convertTypeNames(ret),
        name,
        params: params.length === 1 && params[0] === undefined ? [] : params,
      });
    }
  }

  if (index == files.length - 1) {
    fs.writeFileSync("../apidocs/api.json", JSON.stringify(APIs, undefined, 2));
  }
});
