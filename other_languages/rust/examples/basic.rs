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
