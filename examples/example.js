const parseCLI = require("../");

(async() => {
  const cli = await parseCLI();

  let verbose = false;
  if (cli.noArgs)                  exit("Arguments needed");
  if (cli.s.h || cli.c.help)       exit("Help Menu:\n\nThis is just an example");
  if (cli.s.v || cli.c.verbose)    verbose = true;
  if (cli.c.version)               exit("V0.0.1");
  if (cli.s.s)                     console.log("Hello!");
  if (cli.p)                       console.log("Hello", cli.p);
  if (cli.c?.["debug-arguments"])  console.log(JSON.stringify(cli, null, 4));

})();

const exit = msg => {
  console.log(msg);
  process.exit(0);
}
