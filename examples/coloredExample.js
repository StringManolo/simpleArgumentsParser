import parseCLI from "simpleargumentsparser";

(async() => {
  const cli = await parseCLI();
  
  if (cli.noArgs)                  exit("Arguments needed. Try: --showcase or --help");
  if (cli.s.h || cli.c.help)       exit(getHelpMenu(cli));
  if (cli.c.version)               exit("V1.0.0");
  if (cli.c.showcase)              showColorShowcase(cli);
  if (cli.c.styles)                showStyles(cli);
  if (cli.c.colors)                showColors(cli);
  if (cli.c.bright)                showBrightColors(cli);
  if (cli.c.backgrounds)           showBackgrounds(cli);
  if (cli.c.combinations)          showCombinations(cli);
  if (cli.c.all)                   showAll(cli);
  
})();

const exit = msg => {
  console.log(msg);
  process.exit(0);
}

const getHelpMenu = (cli) => {
  return `
${cli.color.bold.cyan("CLI Color System Showcase")}
${cli.color.dim("=")}${"=".repeat(50)}

${cli.color.bold("Usage:")}
  node example.js [options]

${cli.color.bold("Options:")}
  ${cli.color.green("--showcase")}      Show complete color showcase
  ${cli.color.green("--styles")}        Show text styles (bold, italic, etc.)
  ${cli.color.green("--colors")}        Show basic colors
  ${cli.color.green("--bright")}        Show bright colors
  ${cli.color.green("--backgrounds")}   Show background colors
  ${cli.color.green("--combinations")}  Show style combinations
  ${cli.color.green("--all")}           Show everything
  ${cli.color.green("-h, --help")}      Show this help menu
  ${cli.color.green("--version")}       Show version

${cli.color.bold("Examples:")}
  ${cli.color.dim("$")} node example.js --showcase
  ${cli.color.dim("$")} node example.js --colors --bright
  ${cli.color.dim("$")} node example.js --all
`;
}

const showStyles = (cli) => {
  console.log(`\n${cli.color.bold.underline("TEXT STYLES")}\n`);
  
  console.log(`${cli.color.bold("Bold text")} - Use .bold`);
  console.log(`${cli.color.dim("Dim text")} - Use .dim`);
  console.log(`${cli.color.italic("Italic text")} - Use .italic`);
  console.log(`${cli.color.underline("Underlined text")} - Use .underline`);
  console.log(`${cli.color.blink("Blinking text")} - Use .blink`);
  console.log(`${cli.color.invert("Inverted text")} - Use .invert`);
}

const showColors = (cli) => {
  console.log(`\n${cli.color.bold.underline("BASIC COLORS")}\n`);
  
  console.log(`${cli.color.black("Black text")} - Use .black`);
  console.log(`${cli.color.red("Red text")} - Use .red`);
  console.log(`${cli.color.green("Green text")} - Use .green`);
  console.log(`${cli.color.yellow("Yellow text")} - Use .yellow`);
  console.log(`${cli.color.blue("Blue text")} - Use .blue`);
  console.log(`${cli.color.magenta("Magenta text")} - Use .magenta`);
  console.log(`${cli.color.cyan("Cyan text")} - Use .cyan`);
  console.log(`${cli.color.white("White text")} - Use .white`);
}

const showBrightColors = (cli) => {
  console.log(`\n${cli.color.bold.underline("BRIGHT COLORS")}\n`);
  
  console.log(`${cli.color.brightBlack("Bright Black text")} - Use .brightBlack`);
  console.log(`${cli.color.brightRed("Bright Red text")} - Use .brightRed`);
  console.log(`${cli.color.brightGreen("Bright Green text")} - Use .brightGreen`);
  console.log(`${cli.color.brightYellow("Bright Yellow text")} - Use .brightYellow`);
  console.log(`${cli.color.brightBlue("Bright Blue text")} - Use .brightBlue`);
  console.log(`${cli.color.brightMagenta("Bright Magenta text")} - Use .brightMagenta`);
  console.log(`${cli.color.brightCyan("Bright Cyan text")} - Use .brightCyan`);
  console.log(`${cli.color.brightWhite("Bright White text")} - Use .brightWhite`);
}

const showBackgrounds = (cli) => {
  console.log(`\n${cli.color.bold.underline("BACKGROUND COLORS")}\n`);
  
  console.log(`${cli.color.bgBlack.white("Black background")} - Use .bgBlack`);
  console.log(`${cli.color.bgRed.white("Red background")} - Use .bgRed`);
  console.log(`${cli.color.bgGreen.black("Green background")} - Use .bgGreen`);
  console.log(`${cli.color.bgYellow.black("Yellow background")} - Use .bgYellow`);
  console.log(`${cli.color.bgBlue.white("Blue background")} - Use .bgBlue`);
  console.log(`${cli.color.bgMagenta.white("Magenta background")} - Use .bgMagenta`);
  console.log(`${cli.color.bgCyan.black("Cyan background")} - Use .bgCyan`);
  console.log(`${cli.color.bgWhite.black("White background")} - Use .bgWhite`);
}

const showCombinations = (cli) => {
  console.log(`\n${cli.color.bold.underline("STYLE COMBINATIONS")}\n`);
  
  console.log(`${cli.color.bold.red("Bold Red")} - Use .bold.red`);
  console.log(`${cli.color.italic.green("Italic Green")} - Use .italic.green`);
  console.log(`${cli.color.underline.yellow("Underlined Yellow")} - Use .underline.yellow`);
  console.log(`${cli.color.bold.italic.cyan("Bold Italic Cyan")} - Use .bold.italic.cyan`);
  console.log(`${cli.color.dim.underline.magenta("Dim Underlined Magenta")} - Use .dim.underline.magenta`);
  console.log(`${cli.color.bold.bgRed.white("Bold White on Red")} - Use .bold.bgRed.white`);
  console.log(`${cli.color.italic.bgCyan.black("Italic Black on Cyan")} - Use .italic.bgCyan.black`);
  console.log(`${cli.color.bold.underline.brightGreen("Bold Underlined Bright Green")} - Use .bold.underline.brightGreen`);
}

const showColorShowcase = (cli) => {
  console.log(`\n${cli.color.bold.brightCyan("╔═══════════════════════════════════════╗")}`);
  console.log(`${cli.color.bold.brightCyan("║")}     ${cli.color.bold.white("CLI COLOR SYSTEM SHOWCASE")}     ${cli.color.bold.brightCyan("║")}`);
  console.log(`${cli.color.bold.brightCyan("╚═══════════════════════════════════════╝")}\n`);
  
  showStyles(cli);
  showColors(cli);
  showBrightColors(cli);
  showBackgrounds(cli);
  showCombinations(cli);
  
  console.log(`\n${cli.color.bold.underline("PRACTICAL EXAMPLES")}\n`);
  
  console.log(`${cli.color.green("✓")} ${cli.color.bold("Success:")} Operation completed successfully`);
  console.log(`${cli.color.red("✗")} ${cli.color.bold("Error:")} Something went wrong`);
  console.log(`${cli.color.yellow("⚠")} ${cli.color.bold("Warning:")} Please review your input`);
  console.log(`${cli.color.blue("ℹ")} ${cli.color.bold("Info:")} Processing data...`);
  console.log(`${cli.color.cyan("→")} ${cli.color.bold("Step 1:")} Initialize configuration`);
  console.log(`${cli.color.magenta("♦")} ${cli.color.bold("Debug:")} ${cli.color.dim("Variable x = 42")}`);
  
  console.log(`\n${cli.color.bold.underline("CODE HIGHLIGHTING SIMULATION")}\n`);
  
  console.log(`${cli.color.magenta("const")} ${cli.color.cyan("greeting")} = ${cli.color.green('"Hello"')} + ${cli.color.green('"World"')};`);
  console.log(`${cli.color.magenta("function")} ${cli.color.yellow("sayHello")}() {`);
  console.log(`  ${cli.color.blue("console")}.${cli.color.yellow("log")}(${cli.color.cyan("greeting")});`);
  console.log(`}`);
  
  console.log(`\n${cli.color.bold.underline("MESSAGE TYPES")}\n`);
  
  console.log(`${cli.color.bgGreen.black.bold(" SUCCESS ")} ${cli.color.green("File saved successfully!")}`);
  console.log(`${cli.color.bgRed.white.bold(" ERROR ")} ${cli.color.red("Failed to connect to database")}`);
  console.log(`${cli.color.bgYellow.black.bold(" WARNING ")} ${cli.color.yellow("Deprecated function used")}`);
  console.log(`${cli.color.bgBlue.white.bold(" INFO ")} ${cli.color.blue("Starting server on port 3000...")}`);
  
  console.log(`\n${cli.color.dim("─".repeat(60))}`);
  console.log(`${cli.color.italic.dim("Tip: Chain multiple styles like")} ${cli.color.bold.yellow("cli.color.bold.yellow()")}`);
  console.log(`${cli.color.dim("─".repeat(60))}\n`);
}

const showAll = (cli) => {
  showColorShowcase(cli);
}
