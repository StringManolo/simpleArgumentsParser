const parseCLI = require("./");

(async() => {
  const cli = await parseCLI();
  console.log(cli);
})();
