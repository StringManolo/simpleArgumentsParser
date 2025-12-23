# simpleArgumentsParser

> A lightweight, powerful CLI argument parser for Node.js, Bash, Rust, and C++ with built-in ANSI color support

[![npm version](https://img.shields.io/npm/v/simpleargumentsparser.svg)](https://www.npmjs.com/package/simpleargumentsparser)
[![crates.io](https://img.shields.io/crates/v/simpleargumentsparser.svg)](https://crates.io/crates/simpleargumentsparser)
[![License: GPLV3](https://img.shields.io/badge/License-GPLV3-yellow.svg)](https://opensource.org/licenses/GPLV3)

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Quick Start](#quick-start)
- [API Reference](#api-reference)
  - [Argument Types](#argument-types)
  - [Color System](#color-system)
- [Examples](#examples)
- [Bash Version](#bash-version)
- [Rust Version](#rust-version)
- [C++ Version](#c-version)
- [License](#license)

---

## Overview

**simpleArgumentsParser** is a zero-dependency CLI argument parser designed for simplicity and speed. Unlike heavyweight alternatives, it provides exactly what you need: fast argument parsing, pipe support, and a beautiful color system—all in a compact package.

### Why Choose simpleArgumentsParser?

- **🚀 Fast & Lightweight** - Zero dependencies, minimal overhead
- **🎨 Built-in Colors** - ANSI color system with chainable styles
- **🔄 Pipe Support** - Handle piped input seamlessly
- **📦 Multi-Language** - Available for Node.js (JS/TS), Rust, C++, and Bash
- **🎯 Simple API** - Intuitive syntax, minimal learning curve
- **⚡ TypeScript Ready** - Full TypeScript support with type definitions

---

## Features

✨ **Argument Parsing**
- Single-dash flags (`-v`, `-h`)
- Double-dash options (`--verbose`, `--help`)
- Multi-flag support (`-lvk` → `-l -v -k`)
- Hyphenated options (`--add-new-item`)
- Position tracking for positional arguments
- Piped input detection and handling

🎨 **Color System**
- Text styles (bold, italic, underline, dim, blink, invert)
- 8 standard colors + 8 bright variants
- Background colors
- Chainable style combinations
- Works in Node.js, Rust, C++, and Bash

---

## Installation

### Node.js / npm

```bash
npm install simpleargumentsparser
```

### Rust

```toml
cargo add simpleargumentsparser
```

### C++

```bash
# Copy the single header file
cp other_languages/cpp/simpleargumentsparser.hpp /your/project/include/
```

### Bash

```bash
git clone https://github.com/stringmanolo/simpleargumentsparser
cd simpleargumentsparser/other_languages/bash
# You can also use npm
```

---

## Quick Start

### Node.js (JavaScript)

```javascript
const parseCLI = require("simpleargumentsparser");

(async () => {
  const cli = await parseCLI();

  if (cli.s.h || cli.c.help) {
    console.log(`${cli.color.bold.cyan("My CLI Tool")} - v1.0.0`);
    console.log(`${cli.color.green("✓")} Ready to use!`);
  }
})();
```

### Node.js (TypeScript)

```typescript
import parseCLI from "simpleargumentsparser";

(async () => {
  const cli = await parseCLI();

  if (cli.noArgs) {
    console.log(cli.color.yellow("No arguments provided"));
  }
})();
```

### Rust

```rust
use simpleargumentsparser::parse_cli;
use std::process;

fn main() {
    let cli = parse_cli();

    if cli.s.contains_key("h") || cli.c.contains_key("help") {
        exit("Help Menu:\n\nThis is just an example");
    }
}

fn exit(msg: &str) {
    println!("{}", msg);
    process::exit(0);
}
```

### C++

```cpp
#include "simpleargumentsparser.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  CLI cli = parseCLI(argc, argv);

  if (cli.s["h"] || cli.c["help"]) {
    std::cout << cli.color["bold"]["cyan"]("My C++ Tool") << " v1.0.0" << std::endl;
    return 0;
  }

  return 0;
}
```

### Bash

```bash
#!/bin/bash
source ./parseCLI
parse_cli "$@"

if cli s h || cli c help; then
    cli color bold cyan "My Script v1.0.0"
fi
```

---

## API Reference

### CLI Object Structure

The parser returns an object with the following properties:

```javascript
{
  s: {},        // Single-dash arguments (-v, -h)
  c: {},        // Double-dash arguments (--verbose, --help)
  o: [],        // Positional arguments with position tracking
  p: false,     // Piped input (string or false)
  e: [],        // Separator positions (--)
  noArgs: false,// True if no arguments provided
  argc: 0,      // Argument count (excludes piped input)
  color: {}     // Color system API
}
```

---

### Argument Types

#### `s` - Single-Dash Arguments

Single-dash flags that can be combined or have values.

```bash
# Boolean flags
$ myapp -v -h
```
```javascript
cli.s.v  // true
cli.s.h  // true
```

```bash
# With values
$ myapp -n John -p 3000
```
```javascript
cli.s.n  // "John"
cli.s.p  // "3000"
```

```bash
# Combined flags
$ myapp -lvk
```
```javascript
cli.s.l  // true
cli.s.v  // true
cli.s.k  // true
```

#### `c` - Double-Dash Arguments

Double-dash options that support hyphenated names.

```bash
# Boolean options
$ myapp --verbose --debug
```
```javascript
cli.c.verbose  // true
cli.c.debug    // true
```

```bash
# With values
$ myapp --name John --output-dir ./build
```
```javascript
cli.c.name          // "John"
cli.c["output-dir"] // "./build"
```

#### `o` - Positional Arguments

Non-flag arguments tracked by position.

```bash
$ myapp init project backend
```
```javascript
cli.o  // [["init", 1], ["project", 2], ["backend", 3]]
```

#### `p` - Piped Input

Automatically captured when data is piped into your CLI.

```bash
$ echo "Hello World" | myapp
```
```javascript
cli.p  // "Hello World"
```

```bash
# Combine with arguments
$ cat data.txt | myapp --process
```
```javascript
cli.p          // "Contents of data.txt"
cli.c.process  // true
```

#### `e` - Separators

Track positions of `--` separators for command chaining.

```bash
$ myapp cmd1 -v -- cmd2 -d -- cmd3
```
```javascript
cli.e  // [3, 6]
```

#### `noArgs` & `argc`

Helper properties for quick validation.

```javascript
if (cli.noArgs) {
  console.log("Please provide arguments");
  process.exit(1);
}

console.log(`Received ${cli.argc} argument(s)`);
```

---

### Color System

#### Basic Usage

```javascript
// Direct color application
console.log(cli.color.red("Error message"));
console.log(cli.color.green("Success!"));
console.log(cli.color.blue("Information"));
```

#### Text Styles

```javascript
cli.color.bold("Bold text")
cli.color.dim("Dimmed text")
cli.color.italic("Italic text")
cli.color.underline("Underlined text")
cli.color.blink("Blinking text")
cli.color.invert("Inverted colors")
```

#### Standard Colors

```javascript
cli.color.black("Black")
cli.color.red("Red")
cli.color.green("Green")
cli.color.yellow("Yellow")
cli.color.blue("Blue")
cli.color.magenta("Magenta")
cli.color.cyan("Cyan")
cli.color.white("White")
```

#### Bright Colors

```javascript
cli.color.brightBlack("Bright Black")
cli.color.brightRed("Bright Red")
cli.color.brightGreen("Bright Green")
cli.color.brightYellow("Bright Yellow")
cli.color.brightBlue("Bright Blue")
cli.color.brightMagenta("Bright Magenta")
cli.color.brightCyan("Bright Cyan")
cli.color.brightWhite("Bright White")
```

#### Background Colors

```javascript
cli.color.bgBlack("Black background")
cli.color.bgRed("Red background")
cli.color.bgGreen("Green background")
cli.color.bgYellow("Yellow background")
cli.color.bgBlue("Blue background")
cli.color.bgMagenta("Magenta background")
cli.color.bgCyan("Cyan background")
cli.color.bgWhite("White background")
```

#### Chaining Styles

Combine multiple styles for complex formatting:

```javascript
cli.color.bold.red("Bold red")
cli.color.underline.yellow("Underlined yellow")
cli.color.bold.italic.cyan("Bold italic cyan")
cli.color.bgRed.white.bold("Bold white on red")
cli.color.dim.underline.brightGreen("Complex styling")
```

#### Practical Examples

```javascript
// Status messages
console.log(`${cli.color.green("✓")} ${cli.color.bold("Success:")} File saved`);
console.log(`${cli.color.red("✗")} ${cli.color.bold("Error:")} File not found`);
console.log(`${cli.color.yellow("⚠")} ${cli.color.bold("Warning:")} Deprecated API`);
console.log(`${cli.color.blue("ℹ")} ${cli.color.bold("Info:")} Loading...`);

// Formatted output
const name = "Manolo";
console.log(`Hello ${cli.color.bold.yellow(name)}, welcome!`);

// Status badges
console.log(`${cli.color.bgGreen.black.bold(" SUCCESS ")} Operation completed`);
console.log(`${cli.color.bgRed.white.bold(" ERROR ")} Connection failed`);
console.log(`${cli.color.bgYellow.black.bold(" WARNING ")} Low memory`);

// Code highlighting simulation
console.log(`${cli.color.magenta("const")} ${cli.color.cyan("name")} = ${cli.color.green('"value"')};`);
```

---

## Examples

### Complete CLI Application (Node.js)

```javascript
const parseCLI = require("simpleargumentsparser");

(async () => {
  const cli = await parseCLI();

  // Help menu
  if (cli.s.h || cli.c.help) {
    showHelp(cli);
    process.exit(0);
  }

  // Version
  if (cli.c.version) {
    console.log(cli.color.bold("v1.0.0"));
    process.exit(0);
  }

  // Validation
  if (cli.noArgs && !cli.p) {
    console.log(cli.color.red("Error: No input provided"));
    console.log(`Use ${cli.color.cyan("--help")} for usage information`);
    process.exit(1);
  }

  // Process piped input
  if (cli.p) {
    console.log(cli.color.blue("Processing piped input..."));
    processInput(cli.p);
  }

  // Verbose mode
  const verbose = cli.s.v || cli.c.verbose;
  if (verbose) {
    console.log(cli.color.dim("Verbose mode enabled"));
  }

  // Debug mode
  if (cli.c["debug-args"]) {
    console.log(cli.color.magenta("Debug: Arguments"));
    console.log(JSON.stringify(cli, null, 2));
  }
})();

function showHelp(cli) {
  console.log(`
${cli.color.bold.cyan("My CLI Tool")} ${cli.color.dim("- v1.0.0")}
${cli.color.dim("=")}${"=".repeat(50)}

${cli.color.bold("USAGE")}
  mycli [command] [options]

${cli.color.bold("COMMANDS")}
  ${cli.color.green("init")}        Initialize a new project
  ${cli.color.green("build")}       Build the project
  ${cli.color.green("deploy")}      Deploy to production

${cli.color.bold("OPTIONS")}
  ${cli.color.yellow("-h, --help")}        Show this help message
  ${cli.color.yellow("-v, --verbose")}     Enable verbose output
  ${cli.color.yellow("--version")}         Show version number
  ${cli.color.yellow("--debug-args")}      Show parsed arguments

${cli.color.bold("EXAMPLES")}
  ${cli.color.dim("$")} mycli init --verbose
  ${cli.color.dim("$")} mycli build -v
  ${cli.color.dim("$")} echo "data" | mycli process
  `);
}

function processInput(input) {
  console.log(cli.color.green("✓") + " Processed:", input);
}
```

### TypeScript Example with Type Safety

```typescript
import parseCLI from "simpleargumentsparser";
import * as fs from "fs";

interface Config {
  input: string;
  output: string;
  verbose: boolean;
}

const loadFile = (filename: string): string | null => {
  try {
    return fs.readFileSync(filename, { encoding: "utf-8" });
  } catch (e) {
    return null;
  }
};

(async () => {
  const cli = await parseCLI();

  const config: Config = {
    input: cli.c.input as string || "input.txt",
    output: cli.c.output as string || "output.txt",
    verbose: !!(cli.s.v || cli.c.verbose)
  };

  if (config.verbose) {
    console.log(cli.color.dim(`Input: ${config.input}`));
    console.log(cli.color.dim(`Output: ${config.output}`));
  }

  const content = loadFile(config.input);

  if (!content) {
    console.log(cli.color.red(`Error: Cannot read ${config.input}`));
    process.exit(1);
  }

  // Process content...
  console.log(cli.color.green("✓ Success"));
})();
```

---

## Bash Version

### Installation & Setup

```bash
# Clone or download the repository
git clone https://github.com/stringmanolo/simpleargumentsparser
cd simpleargumentsparser/other_languages/bash

# Source in your script
source ./parseCLI

# Send the commands you want the lib to parse. "$@" for all the cli commands
parse_cli "$@"
```

### Syntax Comparison

| Feature | JavaScript | Bash |
|---------|-----------|------|
| No arguments | `cli.noArgs` | `cli noArgs` |
| Single flag | `cli.s.h` | `cli s h` |
| Double flag | `cli.c.help` | `cli c help` |
| Piped input | `cli.p` | `$(cli p)` |
| Positional args | `cli.o` | `cli o` |
| Color output | `cli.color.red("text")` | `cli color red "text"` |

### Basic Bash Example

```bash
#!/bin/bash
source ./parseCLI
parse_cli "$@"

# Validation
if cli noArgs; then
    cli color red "Error: Arguments required"
    exit 1
fi

# Help
if cli s h || cli c help; then
    cli color bold cyan "My Bash Script v1.0.0"
    echo ""
    cli color green "Usage: $0 [options]"
    exit 0
fi

# Process arguments
verbose=false
if cli s v || cli c verbose; then
    verbose=true
    cli color dim yellow "Verbose mode enabled"
fi

# Handle piped input
if cli p found; then
    cli color blue "Processing piped input..."
    input=$(cli p)
    echo "Received: $input"
fi
```

### Bash Color System

```bash
# Basic colors
cli color red "Error message"
cli color green "Success message"
cli color yellow "Warning"

# Text styles
cli color bold "Bold text"
cli color italic "Italic text"
cli color underline "Underlined"

# Chained styles
cli color bold red "Bold red"
cli color underline yellow "Underlined yellow"
cli color bold white bg_red "White on red background"

# Bright colors
cli color bright_red "Bright red"
cli color bright_green "Bright green"
cli color bright_cyan "Bright cyan"

# Background colors
cli color bg_black white "White on black"
cli color bg_red white "White on red"
cli color bg_green black "Black on green"
```

### Complete Bash Example with Helper Functions

```bash
#!/bin/bash
source ./parseCLI
parse_cli "$@"

# Helper functions
info() {
    cli color cyan "[INFO] $1"
}

success() {
    cli color green "[✓] $1"
}

error() {
    cli color bold red "[✗] $1"
}

warning() {
    cli color yellow "[⚠] $1"
}

show_help() {
    cli color bold cyan "My Bash Tool"
    echo ""
    cli color white "Usage: $0 [command] [options]"
    echo ""
    cli color bold "Commands:"
    echo "  start     Start the service"
    echo "  stop      Stop the service"
    echo "  status    Check status"
    echo ""
    cli color bold "Options:"
    echo "  -h, --help       Show this help"
    echo "  -v, --verbose    Verbose output"
    echo "  --version        Show version"
}

# Main logic
if cli noArgs; then
    error "No arguments provided"
    show_help
    exit 1
fi

if cli s h || cli c help; then
    show_help
    exit 0
fi

if cli c version; then
    cli color bold "Version 1.0.0"
    exit 0
fi

# Verbose mode
verbose=false
if cli s v || cli c verbose; then
    verbose=true
    info "Verbose mode enabled"
fi

# Process commands
if cli o 1 | grep -q "start"; then
    info "Starting service..."
    success "Service started"
elif cli o 1 | grep -q "stop"; then
    info "Stopping service..."
    success "Service stopped"
elif cli o 1 | grep -q "status"; then
    info "Checking status..."
    cli color blue "Service is running"
else
    error "Unknown command"
    show_help
    exit 1
fi

# Debug mode
if cli c debug; then
    warning "Debug mode active"
    cli print
fi
```

### Bash Color Showcase

Run the included color showcase example:

```bash
cd other_languages/bash
./colorsExample.sh
```

> Check [freednsBashClient](https://github.com/stringmanolo/freednsbashclient) for a real app using parseCLI

---

## Rust Version

The Rust version of simpleArgumentsParser provides a type-safe, zero-dependency argument parser with a fluent API for colors.

### Installation

Add to your `Cargo.toml`:

```toml
[dependencies]
simpleargumentsparser = "2.1.0"
```

### Basic Usage

```rust
use simpleargumentsparser::parse_cli;
use std::process;

fn main() {
    let cli = parse_cli();

    let mut verbose = false;

    if cli.no_args {
        exit("Arguments needed");
    }

    if cli.s.contains_key("h") || cli.c.contains_key("help") {
        exit("Help Menu:\n\nThis is just an example");
    }

    if cli.s.contains_key("v") || cli.c.contains_key("verbose") {
        verbose = true;
    }

    if cli.c.contains_key("version") {
        exit("V0.0.1");
    }

    if cli.s.contains_key("s") {
        println!("Hello!");
    }

    if let Some(p) = &cli.p {
        println!("Hello {}", p);
    }

    if cli.c.contains_key("debug-arguments") {
        println!("{:#?}", cli);
    }
}

fn exit(msg: &str) {
    println!("{}", msg);
    process::exit(0);
}
```

### Color System (Builder Pattern)

The Rust version features a fluent builder pattern for color styling:

```rust
use simpleargumentsparser::parse_cli;

fn main() {
    let cli = parse_cli();

    // Basic colors with direct application
    println!("{}", cli.color.red("Error message"));
    println!("{}", cli.color.green("Success!"));
    println!("{}", cli.color.blue("Information"));

    // Chaining styles
    println!("{}", cli.color.bold().red("Bold red text"));
    println!("{}", cli.color.underline().yellow("Underlined yellow"));
    println!("{}", cli.color.bold().italic().cyan("Bold italic cyan"));

    // Bright colors
    println!("{}", cli.color.bright_red("Bright red"));
    println!("{}", cli.color.bright_green("Bright green"));

    // Background colors with chaining
    println!("{}", cli.color.bg_red().white("White text on red background"));
    println!("{}", cli.color.bg_blue().bright_white("Bright white on blue"));

    // Using paint() for explicit styling
    println!("{}", cli.color.bold().underline().paint("Explicitly painted text"));
}
```

### Using the `color!` Macro

For more concise color combinations, use the `color!` macro:

```rust
use simpleargumentsparser::color;

fn main() {
    // Combine multiple styles in one line
    println!("{}", color!(bold red "Bold red text"));
    println!("{}", color!(underline yellow "Underlined yellow"));
    println!("{}", color!(bg_blue bright_white "White on blue background"));
    println!("{}", color!(bold italic cyan "Bold italic cyan"));
    println!("{}", color!(bg_red white blink "Blinking white on red"));
}
```

### CLI Object Structure (Rust)

```rust
pub struct CLI {
    pub s: HashMap<String, String>,      // Single-dash arguments (-v, -h)
    pub c: HashMap<String, String>,      // Double-dash arguments (--verbose, --help)
    pub o: Vec<(String, usize)>,         // Positional arguments with indices
    pub p: Option<String>,               // Piped input (None if no pipe)
    pub e: Vec<usize>,                   // Error indices
    pub no_args: bool,                   // True if no arguments provided
    pub argc: usize,                     // Argument count
    pub color: Color,                    // ANSI color system with builder pattern
}
```

### Running Examples

```bash
# Basic example with arguments
cargo run --example basic -- -v --debug-arguments

# Colored example showcase
cargo run --example colored -- --showcase

# Specific color demonstrations
cargo run --example colored -- --colors
cargo run --example colored -- --bright
cargo run --example colored -- --backgrounds

# The example binary
cargo run --bin cli-example -- -h
cargo run --bin cli-example -- --version
```

### With Piped Input

```bash
# Using echo
echo "Hello from pipe" | cargo run --example basic

# Using cat with a file
cat Cargo.toml | cargo run --example basic -- --debug-arguments

# Combined with arguments
printf "Line 1\nLine 2" | cargo run --bin cli-example -- -v
```

### Features

- **Zero Dependencies** - Pure Rust implementation
- **Builder Pattern** - Fluent API for color styling
- **Memory Safe** - Rust's ownership model ensures safety
- **Macro Support** - `color!` macro for concise styling
- **Cross-Platform** - Works on Windows, macOS, Linux
- **Complete Color System** - 8 standard colors, 8 bright variants, backgrounds, and styles
- **Piped Input Support** - Automatic detection of stdin input

---

## C++ Version

The C++ version of simpleArgumentsParser is a single-header library providing a lightweight, zero-dependency CLI argument parser with full ANSI color support. Designed for C++17 and above, it offers a similar API to the JavaScript and Rust versions with C++ idioms.

### Installation

Simply copy the header file to your project:

```bash
# Copy the single header file
cp other_languages/cpp/simpleargumentsparser.hpp /your/project/include/
```

Or include it directly:

```cpp
#include "simpleargumentsparser.hpp"
```

No build system configuration required - it's header-only!

### Basic Usage

```cpp
#include "simpleargumentsparser.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
  CLI cli = parseCLI(argc, argv);

  // Check for help flag using JSValue's implicit bool conversion
  if (cli.s["h"] || cli.c["help"]) {
    std::cout << cli.color["bold"]["cyan"]("My C++ Tool") << " v1.0.0" << std::endl;
    return 0;
  }

  // Verbose mode
  if (cli.s["v"] || cli.c["verbose"]) {
    std::cout << cli.color["dim"]("Verbose mode enabled") << std::endl;
  }

  // Piped input
  if (!cli.p.empty()) {
    std::cout << "Hello " << cli.color["blue"](cli.p) << std::endl;
  }

  return 0;
}
```

### Color System

The C++ version uses bracket notation for color access:

```cpp
// Basic colors
std::cout << cli.color["red"]("Error message") << std::endl;
std::cout << cli.color["green"]("Success!") << std::endl;

// Text styles
std::cout << cli.color["bold"]("Bold text") << std::endl;
std::cout << cli.color["underline"]("Underlined text") << std::endl;

// Chained styles with bracket notation
std::cout << cli.color["bold"]["red"]("Bold red text") << std::endl;
std::cout << cli.color["underline"]["yellow"]("Underlined yellow") << std::endl;

// Bright colors
std::cout << cli.color["brightRed"]("Bright red") << std::endl;
std::cout << cli.color["brightGreen"]("Bright green") << std::endl;

// Background colors
std::cout << cli.color["bgRed"]["white"]("White on red") << std::endl;
std::cout << cli.color["bgBlue"]["white"]("White on blue") << std::endl;
```

### Complete Example

```cpp
#include "simpleargumentsparser.hpp"
#include <iostream>
#include <cstdlib>

void exit(const std::string& msg) {
  std::cout << msg << std::endl;
  std::exit(0);
}

int main(int argc, char* argv[]) {
  CLI cli = parseCLI(argc, argv);

  bool verbose = false;

  if (cli.noArgs)                  exit("Arguments needed");
  if (cli.s["h"] || cli.c["help"]) exit("Help Menu:\n\nThis is just an example");
  if (cli.s["v"] || cli.c["verbose"]) verbose = true;
  if (cli.c["version"])            exit("V0.0.1");
  if (cli.s["s"])                  std::cout << "Hello!" << std::endl;
  if (!cli.p.empty())              std::cout << "Hello " << cli.p << std::endl;

  if (cli.c["debug-arguments"]) {
    std::string json = cli.toJSON(4, true);  // indent=4, tryUseJQ=true
    if (!json.empty()) {
      std::cout << json << std::endl;
    }
  }

  return 0;
}
```

### Color Showcase Example

```cpp
#include "simpleargumentsparser.hpp"
#include <iostream>
#include <sstream>

using namespace std;

void showColorShowcase(const CLI& cli) {
    cout << "\n" << cli.color["bold"]["brightCyan"]("CLI COLOR SYSTEM SHOWCASE") << "\n\n";
    
    // Text styles
    cout << cli.color["bold"]("Bold text") << "\n";
    cout << cli.color["italic"]("Italic text") << "\n";
    cout << cli.color["underline"]("Underlined text") << "\n\n";
    
    // Standard colors
    cout << cli.color["red"]("Red") << " ";
    cout << cli.color["green"]("Green") << " ";
    cout << cli.color["yellow"]("Yellow") << " ";
    cout << cli.color["blue"]("Blue") << "\n\n";
    
    // Chained combinations
    cout << cli.color["bold"]["red"]("Bold Red") << "\n";
    cout << cli.color["underline"]["green"]("Underlined Green") << "\n";
    cout << cli.color["italic"]["blue"]("Italic Blue") << "\n";
    
    // Background combinations
    cout << cli.color["bgRed"]["white"]("White on Red") << "\n";
    cout << cli.color["bgGreen"]["black"]("Black on Green") << "\n";
}

int main(int argc, char* argv[]) {
    CLI cli = parseCLI(argc, argv);
    
    if (cli.c["showcase"]) {
        showColorShowcase(cli);
    }
    
    return 0;
}
```

### Features

- **Single-header library** - Just include `simpleargumentsparser.hpp`
- **Zero dependencies** - Only uses standard C++17 library
- **Type-safe API** - Uses `std::variant` and `JSValue` wrapper
- **Full ANSI color system** - Bracket notation for colors (`["color"]["style"]`)
- **Cross-platform** - Works on Windows, macOS, and Linux
- **Automatic pipe detection** - Captures piped input automatically
- **JSON output** - Built-in JSON serialization with jq support
- **Debug utilities** - Built-in debugging and visualization

### Compilation

Compile with C++17 or later:

```bash
# Basic compilation
g++ -std=c++17 -o myapp myapp.cpp

# With optimizations
g++ -std=c++17 -O2 -o myapp myapp.cpp
```

### Running Examples

```bash
# Build the examples
g++ -std=c++17 -o example example.cpp
g++ -std=c++17 -o coloredExample coloredExample.cpp

# Run basic example
./example -h
./example -v --debug-arguments

# Run color showcase
./coloredExample --showcase
./coloredExample --colors --bright

# With piped input
echo "Hello from pipe" | ./example
```

---

## Contributing

Contributions are welcome! This library is actively maintained and improved based on real-world usage.

### Reporting Issues

Found a bug or have a feature request? Please open an issue on GitHub with:
- Clear description of the problem/feature
- Steps to reproduce (for bugs)
- Expected vs actual behavior
- Your environment (Node.js version, OS, etc.)

---

## Support

- 📖 **Documentation**: See examples above
- 🐛 **Issues**: [GitHub Issues](https://github.com/stringmanolo/simpleargumentsparser/issues)
- 📦 **npm Package**: [simpleargumentsparser on npm](https://www.npmjs.com/package/simpleargumentsparser)
- 📦 **Crate**: [simpleargumentsparser on crates.io](https://crates.io/crates/simpleargumentsparser)