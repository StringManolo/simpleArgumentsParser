use std::collections::HashMap;
use std::io::{self, BufRead, IsTerminal};
use std::env;

#[derive(Debug)]
pub struct CLI {
    pub s: HashMap<String, String>,
    pub c: HashMap<String, String>,
    pub o: Vec<(String, usize)>,
    pub p: Option<String>,
    pub e: Vec<usize>,
    pub no_args: bool,
    pub argc: usize,
    pub color: Color,
}

#[derive(Debug, Clone)]
pub struct Color {
    codes: Vec<&'static str>,
}

impl Color {
    pub fn new() -> Self {
        Self { codes: Vec::new() }
    }

    fn apply(&self, text: &str) -> String {
        if self.codes.is_empty() {
            return text.to_string();
        }
        format!("{}{}\x1b[0m", self.codes.join(""), text)
    }

    fn add_style(&self, code: &'static str) -> Self {
        let mut new_color = self.clone();
        new_color.codes.push(code);
        new_color
    }

    pub fn bold(&self) -> Self { self.add_style("\x1b[1m") }
    pub fn dim(&self) -> Self { self.add_style("\x1b[2m") }
    pub fn italic(&self) -> Self { self.add_style("\x1b[3m") }
    pub fn underline(&self) -> Self { self.add_style("\x1b[4m") }
    pub fn blink(&self) -> Self { self.add_style("\x1b[5m") }
    pub fn invert(&self) -> Self { self.add_style("\x1b[7m") }

    pub fn fg_black(&self) -> Self { self.add_style("\x1b[30m") }
    pub fn fg_red(&self) -> Self { self.add_style("\x1b[31m") }
    pub fn fg_green(&self) -> Self { self.add_style("\x1b[32m") }
    pub fn fg_yellow(&self) -> Self { self.add_style("\x1b[33m") }
    pub fn fg_blue(&self) -> Self { self.add_style("\x1b[34m") }
    pub fn fg_magenta(&self) -> Self { self.add_style("\x1b[35m") }
    pub fn fg_cyan(&self) -> Self { self.add_style("\x1b[36m") }
    pub fn fg_white(&self) -> Self { self.add_style("\x1b[37m") }

    pub fn black(&self, text: &str) -> String { self.fg_black().apply(text) }
    pub fn red(&self, text: &str) -> String { self.fg_red().apply(text) }
    pub fn green(&self, text: &str) -> String { self.fg_green().apply(text) }
    pub fn yellow(&self, text: &str) -> String { self.fg_yellow().apply(text) }
    pub fn blue(&self, text: &str) -> String { self.fg_blue().apply(text) }
    pub fn magenta(&self, text: &str) -> String { self.fg_magenta().apply(text) }
    pub fn cyan(&self, text: &str) -> String { self.fg_cyan().apply(text) }
    pub fn white(&self, text: &str) -> String { self.fg_white().apply(text) }

    pub fn bright_black(&self, text: &str) -> String { self.add_style("\x1b[90m").apply(text) }
    pub fn bright_red(&self, text: &str) -> String { self.add_style("\x1b[91m").apply(text) }
    pub fn bright_green(&self, text: &str) -> String { self.add_style("\x1b[92m").apply(text) }
    pub fn bright_yellow(&self, text: &str) -> String { self.add_style("\x1b[93m").apply(text) }
    pub fn bright_blue(&self, text: &str) -> String { self.add_style("\x1b[94m").apply(text) }
    pub fn bright_magenta(&self, text: &str) -> String { self.add_style("\x1b[95m").apply(text) }
    pub fn bright_cyan(&self, text: &str) -> String { self.add_style("\x1b[96m").apply(text) }
    pub fn bright_white(&self, text: &str) -> String { self.add_style("\x1b[97m").apply(text) }

    pub fn bg_black(&self) -> Self { self.add_style("\x1b[40m") }
    pub fn bg_red(&self) -> Self { self.add_style("\x1b[41m") }
    pub fn bg_green(&self) -> Self { self.add_style("\x1b[42m") }
    pub fn bg_yellow(&self) -> Self { self.add_style("\x1b[43m") }
    pub fn bg_blue(&self) -> Self { self.add_style("\x1b[44m") }
    pub fn bg_magenta(&self) -> Self { self.add_style("\x1b[45m") }
    pub fn bg_cyan(&self) -> Self { self.add_style("\x1b[46m") }
    pub fn bg_white(&self) -> Self { self.add_style("\x1b[47m") }

    pub fn paint(&self, text: &str) -> String {
        self.apply(text)
    }
}

pub fn parse_cli() -> CLI {
    let args: Vec<String> = env::args().skip(1).collect();
    let argc = args.len();
    let piped_input = get_piped_input();
    let mut short_opts = HashMap::new();
    let mut long_opts = HashMap::new();
    let mut positional = Vec::new();
    let mut errors = Vec::new();
    let mut previous_is_arg = false;

    for (index, current) in args.iter().enumerate() {
        if previous_is_arg {
            previous_is_arg = false;
            continue;
        }
        let next = args.get(index + 1);
        let chars: Vec<char> = current.chars().collect();

        if chars.len() >= 2 && chars[0] == '-' {
            match chars[1] {
                '-' => {
                    if chars.len() >= 3 {
                        let name_of_arg = &current[2..];
                        let is_valid = name_of_arg.chars().all(|c|
                            c.is_ascii_alphanumeric() || c == '-'
                        ) && !name_of_arg.starts_with('-')
                        && !name_of_arg.ends_with('-')
                        && !name_of_arg.contains("--");

                        if is_valid {
                            if let Some(next_val) = next {
                                if next_val.starts_with('-') {
                                    long_opts.insert(name_of_arg.to_string(), "true".to_string());
                                } else {
                                    long_opts.insert(name_of_arg.to_string(), next_val.clone());
                                    previous_is_arg = true;
                                }
                            } else {
                                long_opts.insert(name_of_arg.to_string(), "true".to_string());
                            }
                        } else {
                            positional.push((current.clone(), index + 1));
                        }
                    } else {
                        errors.push(index + 1);
                    }
                }
                _ => {
                    let name_of_arg = &current[1..];
                    let is_valid = name_of_arg.chars().all(|c| c.is_ascii_alphabetic());
                    if is_valid {
                        if name_of_arg.len() > 1 {
                            for c in name_of_arg.chars() {
                                short_opts.insert(c.to_string(), "true".to_string());
                            }
                        } else if let Some(next_val) = next {
                            if next_val.starts_with('-') {
                                short_opts.insert(name_of_arg.to_string(), "true".to_string());
                            } else {
                                short_opts.insert(name_of_arg.to_string(), next_val.clone());
                                previous_is_arg = true;
                            }
                        } else {
                            short_opts.insert(name_of_arg.to_string(), "true".to_string());
                        }
                    } else {
                        positional.push((current.clone(), index + 1));
                    }
                }
            }
        } else {
            positional.push((current.clone(), index + 1));
        }
    }

    let no_args = piped_input.is_none() && argc == 0;
    CLI {
        s: short_opts,
        c: long_opts,
        o: positional,
        p: piped_input,
        e: errors,
        no_args,
        argc,
        color: Color::new(),
    }
}

fn get_piped_input() -> Option<String> {
    if io::stdin().is_terminal() { return None; }
    let stdin = io::stdin();
    let mut lines = Vec::new();
    for line in stdin.lock().lines() {
        if let Ok(l) = line { lines.push(l); }
    }
    if lines.is_empty() { None } else { Some(lines.join("\n")) }
}

#[macro_export]
macro_rules! color {
    ($($style:ident),* $text:expr) => {{
        let mut codes = Vec::new();
        $(
            codes.push(match stringify!($style) {
                "red" => "\x1b[31m",
                "green" => "\x1b[32m",
                "yellow" => "\x1b[33m",
                "blue" => "\x1b[34m",
                "magenta" => "\x1b[35m",
                "cyan" => "\x1b[36m",
                "white" => "\x1b[37m",
                "black" => "\x1b[30m",
                "bright_red" => "\x1b[91m",
                "bright_green" => "\x1b[92m",
                "bright_yellow" => "\x1b[93m",
                "bright_blue" => "\x1b[94m",
                "bright_magenta" => "\x1b[95m",
                "bright_cyan" => "\x1b[96m",
                "bright_white" => "\x1b[97m",
                "bright_black" => "\x1b[90m",
                "bg_red" => "\x1b[41m",
                "bg_green" => "\x1b[42m",
                "bg_yellow" => "\x1b[43m",
                "bg_blue" => "\x1b[44m",
                "bg_magenta" => "\x1b[45m",
                "bg_cyan" => "\x1b[46m",
                "bg_white" => "\x1b[47m",
                "bg_black" => "\x1b[40m",
                "bold" => "\x1b[1m",
                "dim" => "\x1b[2m",
                "italic" => "\x1b[3m",
                "underline" => "\x1b[4m",
                "blink" => "\x1b[5m",
                "invert" => "\x1b[7m",
                _ => "",
            });
        )*
        format!("{}{}\x1b[0m", codes.concat(), $text)
    }};
}
