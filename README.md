# simpleArgumentsParser

### What
A simple typescript/javascript library to parse cli arguments. Perfect to make commands

### Why Use
You can make your own even simplier parser adapted exactly to your code requeriments. But using this library, you can save a lot of time.  
  
Writing custom parsers like i was doing for each command, takes a good amount of time. More even on simpler ones. Just better throw a npm install, a require,  await the parser and you ready to go.

### Why not other?
I created this library because i don't like any of other command parsers i tryied. Some are to basic, others are to big for a simple parsing, others just don't work well and other are to complicated.  
   
I probably will be using this library from now. So i will be finding and fixing errors, improving the code, etc. It's going to get much better. 

### LICENSE
![licenseScreenshot](https://user-images.githubusercontent.com/56775178/160669799-586bed67-a9be-4897-ae31-9445c83d7963.png)

### How to install?

```bash
npm i simpleargumentsparser
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

- #### s   
- s holds single hyphen arguments like -v  
- s allow multiple arguments after a single hyphen like -lvk  
- If text dosn't follow, true is assigned  
- If text follows, takes it as value of argument  
```bash
$ helloworld -n Manolo -vd
```
> s: { n: "Manolo", v: true, d: true }  
  
- #### c  
- c holds double guion arguments like --add    
- c allows guions between words like --add-new-number  
- If text doesn't follow, true is assigned  
- If text follows, takes it as value of argument  
```bash
$ helloworld --name String --last-name Manolo --verbose  
```
> c: { name: "String", 'last-name': "Manolo", verbose: true }  
  
- #### o  
- o holds other arguments (anything else found, except - and -- )  
- o Arguments are followed by a number indicating their position  
```bash
$ helloworld hello how are you
```
> o: [ [ "hello", 1 ], [ "how", 2 ], [ "are", 3 ], [ "you", 4 ] ]  
  
- #### p  
- p holds pipped input data  
- You can use pipped and arguments together  
```bash
$ echo "Hey!" | helloworld -n Manolo  
```
> p: "Hey!",  
> s: { n: 'Manolo' }  

- #### e  
- e holds errors and the some time used double hyphen end command  
- _Errors will be added in the future_  
```bash
$ helloworld -v -- helloworld2 -v -- helloworld3 -v  
```
> e: [ 2, 5 ]  

- #### noArgs  
- noArgs is just a boolean set to true if no arguments provided   
- If pipped is provided, noArgs will remain to false   

- #### argc  
- argc counts the number of arguments  
- __argc doesn't count pipped as an argument__  


### Examples

##### Javascript Example
```javascript
const parseCLI = require("simpleargumentsparser");

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

##### Typescript Example
```typescript
// @ts-shebang
import parseCLI from "simpleargumentsparser";

import * as fs from "fs";
// Load a file as utf-8 encoding 
const loadFile = (filename: string): string | null => {
  let retValue: string | null;
  try {
    retValue = fs.readFileSync(filename, { encoding: "utf-8" })
  } catch(e) {
    retValue = null;
  }
  return retValue ? retValue.substring(0, retValue.length-1) : null;
}


const usage = `Usage: base64 [-d] [FILE]

Base64 encode or decode FILE to standard output

-d      Decode data
`;

(async() => {
  const cli = await parseCLI();

  if (!cli.argc) {
    // Encode cli.p
    if (cli.p) {
      const encoded = Buffer.from(cli.p).toString("base64");
      console.log(encoded);
    } else {
    // if not pipped input, show usage
      console.log("base64: no input to process");
      console.log(usage);
    }
  } else if (cli.argc === 1 && cli.s?.d) {
    // Decode cli.p
    const decoded = Buffer.from(cli.p as string, "base64").toString("ascii");
    console.log(decoded);
  } else if (cli.argc === 2 && cli.s?.d) {
    // Decode from file even if pipped input
    if (cli.s.d !== true) {
      const fileContent = loadFile(cli.s.d);
      if (fileContent) {
        const decoded = Buffer.from(fileContent, "base64").toString("ascii");
	// TODO: check if content can be decoded
	console.log(decoded);
      } else {
        console.log(`base64: ${cli.s.d}: No such file or directory`);
      }
    } else {
      const fileContent = loadFile(cli.o?.[0]?.[0]);
      if (fileContent) {
        const decoded = Buffer.from(fileContent, "base64").toString("ascii");
        // TODO: check if content can be decoded
        console.log(decoded);
      } else {
        console.log(`base64: ${cli.o?.[0]?.[0]}: No such file or directory`);
      }
    }
  } else if (cli.argc === 1) {
    const fileContent = loadFile(cli.o?.[0]?.[0]);
    if (fileContent) {
      const encoded = Buffer.from(fileContent).toString("base64");
      console.log(encoded);
    } else {
      console.log(`base64: ${cli.o?.[0]?.[0]}: No such file or directory`);
    }
  } else {
    console.log("base64: unrecognized arguments");
    console.log(usage);
  }

})();
```
