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
    std::string json = cli.toJSON(4, true);
    if (!json.empty()) {
      std::cout << json << std::endl;
    }

    // cli.debug();
  }

  return 0;
}
