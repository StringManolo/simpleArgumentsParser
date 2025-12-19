#[cfg(test)]
mod tests {
  use simpleargumentsparser::parse_cli;

  #[test]
  fn test_basic_parsing() {
    // Note: In actual tests, you'd need to mock env::args
    // This is just a structure example
    let cli = parse_cli();
    assert_eq!(cli.argc, std::env::args().skip(1).count());
  }
}
