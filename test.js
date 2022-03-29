const parseCLI = require("./index.js");

(async() => {
  const cli = await parseCLI();
  console.log(cli);
})();
