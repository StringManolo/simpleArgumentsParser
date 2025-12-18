import readline from "readline";

// Secuencias de escape ANSI
const ANSI = {
  RESET: '\x1b[0m',
  BOLD: '\x1b[1m',
  DIM: '\x1b[2m',
  ITALIC: '\x1b[3m',
  UNDERLINE: '\x1b[4m',
  BLINK: '\x1b[5m',
  INVERT: '\x1b[7m',
  // Colores de texto
  BLACK: '\x1b[30m',
  RED: '\x1b[31m',
  GREEN: '\x1b[32m',
  YELLOW: '\x1b[33m',
  BLUE: '\x1b[34m',
  MAGENTA: '\x1b[35m',
  CYAN: '\x1b[36m',
  WHITE: '\x1b[37m',
  BRIGHT_BLACK: '\x1b[90m',
  BRIGHT_RED: '\x1b[91m',
  BRIGHT_GREEN: '\x1b[92m',
  BRIGHT_YELLOW: '\x1b[93m',
  BRIGHT_BLUE: '\x1b[94m',
  BRIGHT_MAGENTA: '\x1b[95m',
  BRIGHT_CYAN: '\x1b[96m',
  BRIGHT_WHITE: '\x1b[97m',
  // Colores de fondo
  BG_BLACK: '\x1b[40m',
  BG_RED: '\x1b[41m',
  BG_GREEN: '\x1b[42m',
  BG_YELLOW: '\x1b[43m',
  BG_BLUE: '\x1b[44m',
  BG_MAGENTA: '\x1b[45m',
  BG_CYAN: '\x1b[46m',
  BG_WHITE: '\x1b[47m'
};

// Sistema de colores con encadenamiento
const createStyleProxy = (accumulatedCodes: string[] = []): any => {
  const handler = {
    get(target: any, prop: string) {
      const upperProp = prop.toUpperCase();
      
      // Manejar bright* como BRIGHT_*
      let ansiKey = upperProp;
      if (prop.startsWith('bright') && prop.length > 6) {
        const colorName = prop.slice(6).toUpperCase();
        ansiKey = `BRIGHT_${colorName}`;
      }
      
      // Manejar bg* como BG_*
      if (prop.startsWith('bg') && prop.length > 2) {
        const colorName = prop.slice(2).toUpperCase();
        ansiKey = `BG_${colorName}`;
      }
      
      if (ANSI[ansiKey as keyof typeof ANSI]) {
        return createStyleProxy([...accumulatedCodes, ANSI[ansiKey as keyof typeof ANSI]]);
      }
      
      if (typeof target === 'function') {
        return target;
      }
      
      return createStyleProxy(accumulatedCodes);
    },
    apply(target: any, thisArg: any, args: any[]) {
      const text = args[0];
      return accumulatedCodes.join('') + text + ANSI.RESET;
    }
  };
  
  const fn = function(text: string) {
    return accumulatedCodes.join('') + text + ANSI.RESET;
  };
  
  return new Proxy(fn, handler);
};

// Objeto principal color
const color = new Proxy({}, {
  get(target, prop: string) {
    const upperProp = prop.toUpperCase();
    
    // Manejar bright* como BRIGHT_*
    let ansiKey = upperProp;
    if (prop.startsWith('bright') && prop.length > 6) {
      const colorName = prop.slice(6).toUpperCase();
      ansiKey = `BRIGHT_${colorName}`;
    }
    
    // Manejar bg* como BG_*
    if (prop.startsWith('bg') && prop.length > 2) {
      const colorName = prop.slice(2).toUpperCase();
      ansiKey = `BG_${colorName}`;
    }
    
    if (ANSI[ansiKey as keyof typeof ANSI]) {
      return createStyleProxy([ANSI[ansiKey as keyof typeof ANSI]]);
    }
    
    return createStyleProxy([]);
  }
});

interface Is {
  [key: string]: string | boolean
}

interface Ic {
  [key: string]: string | boolean
}

type StringNumberTuple = [string, number]

interface Icli {
  s: Is,
  c: Ic,
  o: StringNumberTuple[],
  p: string | false,
  e: number[],
  noArgs: boolean,
  argc: number,
  color: typeof color
}

const CLI: Icli = {
  s: {}, // single
  c: {}, // couple
  o: [], // other
  p: false, // pipped
  e: [], // end
  noArgs: false,
  argc: process.argv.length - 2,
  color: color
};

const getPippedInput = async(): Promise<string> => {
  return new Promise( (resolve, reject) => {
    if (!process.stdin.isTTY) {
      const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout,
        terminal: false
      });
      let lines = "";
      let linesCounter = 0;
      rl.on("line", line => {
        lines += line + "\n";
        ++linesCounter;
      });
      rl.on("close", () => {
        if (linesCounter > 1) {
          if (lines[lines.length-1] === "\n") {
            lines = lines.substring(0, lines.length-1);
          }
        } else if (linesCounter === 1) {
          if (lines[lines.length-1] === "\n") {
            lines = lines.substring(0, lines.length-1);
          }
        }
        resolve(lines);
      });
    } else {
      reject("Not pipped input");
    }
  })
}

const numberOfArgs = process.argv.length - 2;

const parseCLI = async () => {
  try {
    CLI.p = await getPippedInput();
  } catch(err) {
    CLI.p = false;
  }
  let previousIsArg = false;
  process.argv.splice(2).forEach( (current, index, arr) => {
    if (previousIsArg) {
      previousIsArg = false;
      return;
    }
    const next = arr[index + 1];
    const [fc, sc, tc] = current.split("").splice(0, 3);
    switch(fc) {
      case "-":
        switch(sc) {
          case "-":
            if (tc) {
              const nameOfArg = current.substring(2, current.length);
              //if (/^[a-zA-Z]+$/g.test(nameOfArg)) { // allow guions between words
              if (/^[a-zA-Z0-9]+(?:-[a-zA-Z0-9]+)*$/g.test(nameOfArg)) {
                if (next && next[0] === "-" || next?.substring(0, 2) === "--") {
                  // next arg is an argument too
                  CLI.c[nameOfArg] = true;
                  return
                }
                CLI.c[nameOfArg] = next ? next : true;
                previousIsArg = true;
                return;
              } else { // not valid --a to Z word
                CLI.o.push([current, index + 1]);
              }
            } else {
              CLI.e.push(index + 1);
              // separator found. Ex: cat hello.txt -- echo "abc"
            }
          break;
          default: // parse -v -h ...
            if (sc) {
              const nameOfArg = current.substring(1, current.length);
              if (/^[a-zA-Z]+$/g.test(nameOfArg)) {
                if (next && next[0] === "-" || next?.substring(0, 2) === "--") {
                  // next arg is an argument too
                  CLI.s[nameOfArg] = true;
                  return;
                }
                // parse multiple args like -lvk
                if (nameOfArg.length > 1 && /^[a-zA-Z]+$/g.test(nameOfArg)) {
                  nameOfArg.split("").forEach( arg => CLI.s[arg] = true );
                  return;
                }
                CLI.s[nameOfArg] = next ? next : true;
                previousIsArg = true;
                return
              } else {
                //console.log`WHAT IS THIS??? (${current})`);
              }
            } else {
              //console.log`WHAT IS THIS2??? (${current})`);
              // is not -word && not --word
          }
        }
      break;
      default:
        CLI.o.push([current, index + 1]);
        return;
    }
  });
  if (!CLI.p && !numberOfArgs) {
    CLI.noArgs = true
  }
  return Object.freeze(CLI);
}

module.exports = parseCLI; // node require export
export default parseCLI; // typescript export
