# Rust Version

## Installation

```bash
cargo add simpleargumentsparser
```

## Quick Start

### Basic Example

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
    
    if verbose {
        println!("Verbose mode is on");
    }
}

fn exit(msg: &str) {
    println!("{}", msg);
    process::exit(0);
}
```

## Color System

### Chaining API (Builder Pattern)

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

### Complete Color Showcase

Run the built-in color showcase:

```bash
cargo run --example colored -- --showcase
cargo run --example colored -- --all
cargo run --example colored -- --help
```

## CLI Object Structure

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

## Examples

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

## Features

- **Zero Dependencies** - Pure Rust implementation
- **Builder Pattern** - Fluent API for color styling
- **Memory Safe** - Rust's ownership model ensures safety
- **Macro Support** - `color!` macro for concise styling
- **Cross-Platform** - Works on Windows, macOS, Linux
- **Complete Color System** - 8 standard colors, 8 bright variants, backgrounds, and styles
- **Piped Input Support** - Automatic detection of stdin input

## Color Methods Reference

### Text Colors (Direct Application)
- `black(text: &str) -> String`
- `red(text: &str) -> String`
- `green(text: &str) -> String`
- `yellow(text: &str) -> String`
- `blue(text: &str) -> String`
- `magenta(text: &str) -> String`
- `cyan(text: &str) -> String`
- `white(text: &str) -> String`

### Bright Colors (Direct Application)
- `bright_black(text: &str) -> String`
- `bright_red(text: &str) -> String`
- `bright_green(text: &str) -> String`
- `bright_yellow(text: &str) -> String`
- `bright_blue(text: &str) -> String`
- `bright_magenta(text: &str) -> String`
- `bright_cyan(text: &str) -> String`
- `bright_white(text: &str) -> String`

### Style Modifiers (Chainable)
- `bold() -> Self`
- `dim() -> Self`
- `italic() -> Self`
- `underline() -> Self`
- `blink() -> Self`
- `invert() -> Self`

### Foreground Colors (Chainable)
- `fg_black() -> Self`
- `fg_red() -> Self`
- `fg_green() -> Self`
- `fg_yellow() -> Self`
- `fg_blue() -> Self`
- `fg_magenta() -> Self`
- `fg_cyan() -> Self`
- `fg_white() -> Self`

### Background Colors (Chainable)
- `bg_black() -> Self`
- `bg_red() -> Self`
- `bg_green() -> Self`
- `bg_yellow() -> Self`
- `bg_blue() -> Self`
- `bg_magenta() -> Self`
- `bg_cyan() -> Self`
- `bg_white() -> Self`

### Application Methods
- `apply(text: &str) -> String`
- `paint(text: &str) -> String` (alias for `apply`)

## Real-World Example

```rust
use simpleargumentsparser::parse_cli;
use std::process;

fn main() {
    let cli = parse_cli();
    
    // Help with styled output
    if cli.s.contains_key("h") || cli.c.contains_key("help") {
        println!("{}", cli.color.bold().cyan("My Rust CLI"));
        println!("{}", cli.color.dim().paint("Version 1.0.0"));
        println!("\n{}", cli.color.bold().paint("Usage:"));
        println!("  myapp [options]");
        println!("\n{}", cli.color.bold().paint("Options:"));
        println!("  {} Show this help", cli.color.green("-h, --help"));
        println!("  {} Verbose output", cli.color.green("-v, --verbose"));
        println!("  {} Show version", cli.color.green("--version"));
        process::exit(0);
    }
    
    // Status messages with icons
    println!("{} {}", cli.color.green("✓"), cli.color.bold().paint("Operation successful"));
    println!("{} {}", cli.color.red("✗"), "Something went wrong");
    println!("{} {}", cli.color.yellow("⚠"), "Warning: Deprecated feature");
    
    // Formatted output with chained styles
    let username = "John";
    println!("Hello, {}!", cli.color.bold().yellow(username));
    
    // Code highlighting
    println!("{} {} = {};", 
        cli.color.magenta("let"),
        cli.color.cyan("count"),
        cli.color.green("42")
    );
}
```
