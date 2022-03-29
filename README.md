# simpleArgumentsParser

### What
A simple library to parse cli arguments. Perfect to make commands

### Why Use
You can make your own even simplier parser adapted exactly to your code requeriments. But using this library, you can save a lot of time. Writing custom parsers like i was doing for each command, takes a good amount of time. More even on simpier ones. Just better throw a npm install, a require await the parser and you ready to go.

### Why not other?
I created this library because i don't like any of other command parsers i tryied. Some are to basic, others are to bug for a simple parsing, others just don't work well and other are to complicated.  
I probably will be using this library from now. So i will be finding and fixing errors, improving the code, etc. It's going to get much better. 

### How to install?

```bash
npm i THIS_PACKAGE_IS_NOT_YET_IN_NPM
```

### Basic usage

Arguments are short to reduce time programming.  
```javascript
const CLI = {
  s: {}, // single
  c: {}, // couple
  o: [], // other
  p: {}, // pipped
  e: [], // end
  noArgs: false,
  argc: process.argv.length - 2
};
```

- s  
s holds single hyphen arguments like -v  
s allow multiple arguments after a single hyphen like -lvk  
If text dosn't follow, true is assigned  
If text follows, takes it as value of argument  
Ex: $ helloworld -n Manolo -vd  
s: { n: "Manolo", v: true, d: true }  
  
- c
c holds double guion arguments like --add  
c allows guions between words like --add-new-number  
If text doesn't follow, true is assigned  
If text follows, takes it as value of argument  
Ex: $ helloworld --name String --last-name Manolo --verbose  
c: { name: "String", 'last-name': "Manolo", verbose: true }  
  
- o
o holds other arguments (anything else found, except - and -- )  
o Arguments are followed by a number indicating their position  
Ex: $ helloworld hello how are you  
o: [ [ "hello", 1 ], [ "how", 2 ], [ "are", 3 ], [ "you", 4 ] ]  
  
- p
p holds pipped input data  
You can use pipped and arguments together  
Ex: $ echo "Hey!" | helloworld -n Manolo  
p: "Hey!",  
s: { n: 'Manolo' }  

- e
e holds errors and the some time used double hyphen end command  
_Errors will be added in the future_  
Ex: $ helloworld -v -- helloworld2 -v -- helloworld3 -v  
e: [ 2, 5 ]  

- noArgs
noArgs is just a boolean set to true if no arguments provided  
If pipped is provided, noArgs will remain to false  

- argc
argc counts the number of arguments  
__argc doesn't count pipped as an argument__  


```javascript
const parseCLI = require("./index.js"); // TODO: Add npm name

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
```


