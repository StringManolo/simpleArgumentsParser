use simpleargumentsparser::{parse_cli, CLI};
use std::process;

fn main() {
    let cli = parse_cli();

    if cli.no_args {
        exit("Arguments needed. Try: --showcase or --help");
    }

    if cli.s.contains_key("h") || cli.c.contains_key("help") {
        exit(&get_help_menu(&cli));
    }

    if cli.c.contains_key("version") {
        exit("V1.0.0");
    }

    if cli.c.contains_key("showcase") {
        show_color_showcase(&cli);
    }
    if cli.c.contains_key("styles") {
        show_styles(&cli);
    }
    if cli.c.contains_key("colors") {
        show_colors(&cli);
    }
    if cli.c.contains_key("bright") {
        show_bright_colors(&cli);
    }
    if cli.c.contains_key("backgrounds") {
        show_backgrounds(&cli);
    }
    if cli.c.contains_key("combinations") {
        show_combinations(&cli);
    }
    if cli.c.contains_key("all") {
        show_all(&cli);
    }
}

fn exit(msg: &str) {
    println!("{}", msg);
    process::exit(0);
}

fn get_help_menu(cli: &CLI) -> String {
    format!(
        "\n{}\n{}\n\n{}\n  cargo run -- [options]\n\n{}\n  {}      Show complete color showcase\n  {}        Show text styles (bold, italic, etc.)\n  {}        Show basic colors\n  {}        Show bright colors\n  {}   Show background colors\n  {} Show style combinations\n  {}           Show everything\n  {}      Show this help menu\n  {}       Show version\n\n{}\n  {} cargo run -- --showcase\n  {} cargo run -- --colors --bright\n  {} cargo run -- --all\n",
        cli.color.bold().cyan("CLI Color System Showcase"),
        cli.color.dim().paint("===================================================="),
        cli.color.bold().paint("Usage:"),
        cli.color.bold().paint("Options:"),
        cli.color.green("--showcase"),
        cli.color.green("--styles"),
        cli.color.green("--colors"),
        cli.color.green("--bright"),
        cli.color.green("--backgrounds"),
        cli.color.green("--combinations"),
        cli.color.green("--all"),
        cli.color.green("-h, --help"),
        cli.color.green("--version"),
        cli.color.bold().paint("Examples:"),
        cli.color.dim().paint("$"),
        cli.color.dim().paint("$"),
        cli.color.dim().paint("$")
    )
}

fn show_styles(cli: &CLI) {
    println!("\n{}\n", cli.color.bold().underline().paint("TEXT STYLES"));
    println!("{} - Use .bold()", cli.color.bold().paint("Bold text"));
    println!("{} - Use .dim()", cli.color.dim().paint("Dim text"));
    println!("{} - Use .italic()", cli.color.italic().paint("Italic text"));
    println!("{} - Use .underline()", cli.color.underline().paint("Underlined text"));
    println!("{} - Use .blink()", cli.color.blink().paint("Blinking text"));
    println!("{} - Use .invert()", cli.color.invert().paint("Inverted text"));
}

fn show_colors(cli: &CLI) {
    println!("\n{}\n", cli.color.bold().underline().paint("BASIC COLORS"));
    println!("{} - Use .black()", cli.color.black("Black text"));
    println!("{} - Use .red()", cli.color.red("Red text"));
    println!("{} - Use .green()", cli.color.green("Green text"));
    println!("{} - Use .yellow()", cli.color.yellow("Yellow text"));
    println!("{} - Use .blue()", cli.color.blue("Blue text"));
    println!("{} - Use .magenta()", cli.color.magenta("Magenta text"));
    println!("{} - Use .cyan()", cli.color.cyan("Cyan text"));
    println!("{} - Use .white()", cli.color.white("White text"));
}

fn show_bright_colors(cli: &CLI) {
    println!("\n{}\n", cli.color.bold().underline().paint("BRIGHT COLORS"));
    println!("{} - Use .bright_black()", cli.color.bright_black("Bright Black text"));
    println!("{} - Use .bright_red()", cli.color.bright_red("Bright Red text"));
    println!("{} - Use .bright_green()", cli.color.bright_green("Bright Green text"));
    println!("{} - Use .bright_yellow()", cli.color.bright_yellow("Bright Yellow text"));
    println!("{} - Use .bright_blue()", cli.color.bright_blue("Bright Blue text"));
    println!("{} - Use .bright_magenta()", cli.color.bright_magenta("Bright Magenta text"));
    println!("{} - Use .bright_cyan()", cli.color.bright_cyan("Bright Cyan text"));
    println!("{} - Use .bright_white()", cli.color.bright_white("Bright White text"));
}

fn show_backgrounds(cli: &CLI) {
    println!("\n{}\n", cli.color.bold().underline().paint("BACKGROUND COLORS"));
    println!("{} - Use .bg_black().white()", cli.color.bg_black().white("Black background"));
    println!("{} - Use .bg_red().white()", cli.color.bg_red().white("Red background"));
    println!("{} - Use .bg_green().black()", cli.color.bg_green().black("Green background"));
    println!("{} - Use .bg_yellow().black()", cli.color.bg_yellow().black("Yellow background"));
    println!("{} - Use .bg_blue().white()", cli.color.bg_blue().white("Blue background"));
    println!("{} - Use .bg_magenta().white()", cli.color.bg_magenta().white("Magenta background"));
    println!("{} - Use .bg_cyan().black()", cli.color.bg_cyan().black("Cyan background"));
    println!("{} - Use .bg_white().black()", cli.color.bg_white().black("White background"));
}

fn show_combinations(cli: &CLI) {
    println!("\n{}\n", cli.color.bold().underline().paint("STYLE COMBINATIONS"));
    println!("{} - Use .bold().red()", cli.color.bold().red("Bold Red"));
    println!("{} - Use .italic().green()", cli.color.italic().green("Italic Green"));
    println!("{} - Use .underline().yellow()", cli.color.underline().yellow("Underlined Yellow"));
    println!("{} - Use .bold().italic().cyan()", cli.color.bold().italic().cyan("Bold Italic Cyan"));
    println!("{} - Use .dim().underline().magenta()", cli.color.dim().underline().magenta("Dim Underlined Magenta"));
    println!("{} - Use .bold().bg_red().white()", cli.color.bold().bg_red().white("Bold White on Red"));
    println!("{} - Use .italic().bg_cyan().black()", cli.color.italic().bg_cyan().black("Italic Black on Cyan"));
    println!("{} - Use .bold().underline().bright_green()", cli.color.bold().underline().bright_green("Bold Underlined Bright Green"));
}

fn show_color_showcase(cli: &CLI) {
    println!("\n{}", cli.color.bold().bright_cyan("╔═══════════════════════════════════════╗"));
    println!("{}     {}     {}", cli.color.bold().bright_cyan("║"), cli.color.bold().white("CLI COLOR SYSTEM SHOWCASE"), cli.color.bold().bright_cyan("║"));
    println!("{}\n", cli.color.bold().bright_cyan("╚═══════════════════════════════════════╝"));

    show_styles(cli);
    show_colors(cli);
    show_bright_colors(cli);
    show_backgrounds(cli);
    show_combinations(cli);

    println!("\n{}\n", cli.color.bold().underline().paint("PRACTICAL EXAMPLES"));
    println!("{} {} Operation completed successfully", cli.color.green("✓"), cli.color.bold().paint("Success:"));
    println!("{} {} Something went wrong", cli.color.red("✗"), cli.color.bold().paint("Error:"));
    println!("{} {} Please review your input", cli.color.yellow("⚠"), cli.color.bold().paint("Warning:"));
    println!("{} {} Processing data...", cli.color.blue("ℹ"), cli.color.bold().paint("Info:"));
    println!("{} {} Initialize configuration", cli.color.cyan("→"), cli.color.bold().paint("Step 1:"));
    println!("{} {} {}", cli.color.magenta("♦"), cli.color.bold().paint("Debug:"), cli.color.dim().paint("Variable x = 42"));

    println!("\n{}\n", cli.color.bold().underline().paint("CODE HIGHLIGHTING SIMULATION"));
    println!("{}{} = {} + {};", cli.color.magenta("let "), cli.color.cyan("greeting"), cli.color.green("\"Hello\""), cli.color.green("\"World\""));
    println!("{}{} {{", cli.color.magenta("fn "), cli.color.yellow("say_hello()"));
    println!("  {}.{}({});", cli.color.blue("println!"), cli.color.yellow("format"), cli.color.cyan("greeting"));
    println!("}}");

    println!("\n{}\n", cli.color.bold().underline().paint("MESSAGE TYPES"));
    // Corregido: .fg_black() y .fg_white() para permitir encadenar .bold().paint()
    println!("{} {}", cli.color.bg_green().fg_black().bold().paint(" SUCCESS "), cli.color.green("File saved successfully!"));
    println!("{} {}", cli.color.bg_red().fg_white().bold().paint(" ERROR "), cli.color.red("Failed to connect to database"));
    println!("{} {}", cli.color.bg_yellow().fg_black().bold().paint(" WARNING "), cli.color.yellow("Deprecated function used"));
    println!("{} {}", cli.color.bg_blue().fg_white().bold().paint(" INFO "), cli.color.blue("Starting server on port 3000..."));

    println!("\n{}", cli.color.dim().paint("------------------------------------------------------------"));
    println!("{} {}", cli.color.italic().dim().paint("Tip: Chain multiple styles like"), cli.color.bold().yellow("cli.color.bold().yellow(\"text\")"));
    println!("{}\n", cli.color.dim().paint("------------------------------------------------------------"));
}

fn show_all(cli: &CLI) {
    show_color_showcase(cli);
}
