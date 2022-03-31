"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const readline_1 = __importDefault(require("readline"));
const CLI = {
    s: {},
    c: {},
    o: [],
    p: false,
    e: [],
    noArgs: false,
    argc: process.argv.length - 2
};
const getPippedInput = () => __awaiter(void 0, void 0, void 0, function* () {
    return new Promise((resolve, reject) => {
        if (!process.stdin.isTTY) {
            const rl = readline_1.default.createInterface({
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
                    if (lines[lines.length - 1] === "\n") {
                        lines = lines.substring(0, lines.length - 1);
                    }
                }
                else if (linesCounter === 1) {
                    if (lines[lines.length - 1] === "\n") {
                        lines = lines.substring(0, lines.length - 1);
                    }
                }
                resolve(lines);
            });
        }
        else {
            reject("Not pipped input");
        }
    });
});
const numberOfArgs = process.argv.length - 2;
const parseCLI = () => __awaiter(void 0, void 0, void 0, function* () {
    try {
        CLI.p = yield getPippedInput();
    }
    catch (err) {
        CLI.p = false;
    }
    let previousIsArg = false;
    process.argv.splice(2).forEach((current, index, arr) => {
        if (previousIsArg) {
            previousIsArg = false;
            return;
        }
        const next = arr[index + 1];
        const [fc, sc, tc] = current.split("").splice(0, 3);
        switch (fc) {
            case "-":
                switch (sc) {
                    case "-":
                        if (tc) {
                            const nameOfArg = current.substring(2, current.length);
                            //if (/^[a-zA-Z]+$/g.test(nameOfArg)) { // allow guions between words
                            if (/^[a-zA-Z0-9]+(?:-[a-zA-Z0-9]+)*$/g.test(nameOfArg)) {
                                if (next && next[0] === "-" || (next === null || next === void 0 ? void 0 : next.substring(0, 2)) === "--") {
                                    // next arg is an argument too
                                    CLI.c[nameOfArg] = true;
                                    return;
                                }
                                CLI.c[nameOfArg] = next ? next : true;
                                previousIsArg = true;
                                return;
                            }
                            else { // not valid --a to Z word
                                CLI.o.push([current, index + 1]);
                            }
                        }
                        else {
                            CLI.e.push(index + 1);
                            // separator found. Ex: cat hello.txt -- echo "abc"
                        }
                        break;
                    default: // parse -v -h ...
                        if (sc) {
                            const nameOfArg = current.substring(1, current.length);
                            if (/^[a-zA-Z]+$/g.test(nameOfArg)) {
                                if (next && next[0] === "-" || (next === null || next === void 0 ? void 0 : next.substring(0, 2)) === "--") {
                                    // next arg is an argument too
                                    CLI.s[nameOfArg] = true;
                                    return;
                                }
                                // parse multiple args like -lvk
                                if (nameOfArg.length > 1 && /^[a-zA-Z]+$/g.test(nameOfArg)) {
                                    nameOfArg.split("").forEach(arg => CLI.s[arg] = true);
                                    return;
                                }
                                CLI.s[nameOfArg] = next ? next : true;
                                previousIsArg = true;
                                return;
                            }
                            else {
                                //console.log(`WHAT IS THIS??? (${current})`);
                            }
                        }
                        else {
                            //console.log(`WHAT IS THIS2??? (${current})`);
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
        CLI.noArgs = true;
    }
    return Object.freeze(CLI);
});
module.exports = parseCLI;
