const parseCLI = require("simpleargumentsparser");

(async() => {
  const cli = await parseCLI();
  console.log(cli);
})();
