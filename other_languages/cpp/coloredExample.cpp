#include "simpleargumentsparser.hpp"
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

void exit(const string& msg) {
    cout << msg << endl;
    std::exit(0);
}

string getHelpMenu(const CLI& cli) {
    stringstream help;
    
    help << "\n";
    help << cli.color["bold"]["cyan"]("CLI Color System Showcase") << "\n";
    help << cli.color["dim"]("=") << string(50, '=') << "\n\n";
    
    help << cli.color["bold"]("Usage:") << "\n";
    help << "  ./colored_example [options]\n\n";
    
    help << cli.color["bold"]("Options:") << "\n";
    help << "  " << cli.color["green"]("--showcase") << "      Show complete color showcase\n";
    help << "  " << cli.color["green"]("--styles") << "        Show text styles (bold, italic, etc.)\n";
    help << "  " << cli.color["green"]("--colors") << "        Show basic colors\n";
    help << "  " << cli.color["green"]("--bright") << "        Show bright colors\n";
    help << "  " << cli.color["green"]("--backgrounds") << "   Show background colors\n";
    help << "  " << cli.color["green"]("--combinations") << "  Show style combinations\n";
    help << "  " << cli.color["green"]("--all") << "           Show everything\n";
    help << "  " << cli.color["green"]("-h, --help") << "      Show this help menu\n";
    help << "  " << cli.color["green"]("--version") << "       Show version\n\n";
    
    help << cli.color["bold"]("Examples:") << "\n";
    help << "  " << cli.color["dim"]("$") << " ./colored_example --showcase\n";
    help << "  " << cli.color["dim"]("$") << " ./colored_example --colors --bright\n";
    help << "  " << cli.color["dim"]("$") << " ./colored_example --all\n";
    
    return help.str();
}

void showStyles(const CLI& cli) {
    cout << "\n" << cli.color["bold"]["underline"]("TEXT STYLES") << "\n\n";
    
    cout << cli.color["bold"]("Bold text") << " - Use [\"bold\"]\n";
    cout << cli.color["dim"]("Dim text") << " - Use [\"dim\"]\n";
    cout << cli.color["italic"]("Italic text") << " - Use [\"italic\"]\n";
    cout << cli.color["underline"]("Underlined text") << " - Use [\"underline\"]\n";
    cout << cli.color["blink"]("Blinking text") << " - Use [\"blink\"]\n";
    cout << cli.color["invert"]("Inverted text") << " - Use [\"invert\"]\n";
}

void showColors(const CLI& cli) {
    cout << "\n" << cli.color["bold"]["underline"]("BASIC COLORS") << "\n\n";
    
    cout << cli.color["red"]("Red text") << " - Use [\"red\"]\n";
    cout << cli.color["green"]("Green text") << " - Use [\"green\"]\n";
    cout << cli.color["yellow"]("Yellow text") << " - Use [\"yellow\"]\n";
    cout << cli.color["blue"]("Blue text") << " - Use [\"blue\"]\n";
    cout << cli.color["magenta"]("Magenta text") << " - Use [\"magenta\"]\n";
    cout << cli.color["cyan"]("Cyan text") << " - Use [\"cyan\"]\n";
    cout << cli.color["white"]("White text") << " - Use [\"white\"]\n";
}

void showBrightColors(const CLI& cli) {
    cout << "\n" << cli.color["bold"]["underline"]("BRIGHT COLORS") << "\n\n";
    
    cout << cli.color["brightRed"]("Bright Red text") << " - Use [\"brightRed\"]\n";
    cout << cli.color["brightGreen"]("Bright Green text") << " - Use [\"brightGreen\"]\n";
    cout << cli.color["brightYellow"]("Bright Yellow text") << " - Use [\"brightYellow\"]\n";
    cout << cli.color["brightBlue"]("Bright Blue text") << " - Use [\"brightBlue\"]\n";
    cout << cli.color["brightMagenta"]("Bright Magenta text") << " - Use [\"brightMagenta\"]\n";
    cout << cli.color["brightCyan"]("Bright Cyan text") << " - Use [\"brightCyan\"]\n";
}

void showBackgrounds(const CLI& cli) {
    cout << "\n" << cli.color["bold"]["underline"]("BACKGROUND COLORS") << "\n\n";
    
    cout << cli.color["bgBlack"]["white"]("Black background") << " - Use [\"bgBlack\"][\"white\"]\n";
    cout << cli.color["bgRed"]["white"]("Red background") << " - Use [\"bgRed\"][\"white\"]\n";
    cout << cli.color["bgGreen"]["black"]("Green background") << " - Use [\"bgGreen\"][\"black\"]\n";
    cout << cli.color["bgYellow"]["black"]("Yellow background") << " - Use [\"bgYellow\"][\"black\"]\n";
    cout << cli.color["bgBlue"]["white"]("Blue background") << " - Use [\"bgBlue\"][\"white\"]\n";
}

void showCombinations(const CLI& cli) {
    cout << "\n" << cli.color["bold"]["underline"]("STYLE COMBINATIONS") << "\n\n";
    
    cout << cli.color["bold"]["red"]("Bold Red") << " - Use [\"bold\"][\"red\"]\n";
    cout << cli.color["italic"]["green"]("Italic Green") << " - Use [\"italic\"][\"green\"]\n";
    cout << cli.color["underline"]["yellow"]("Underlined Yellow") << " - Use [\"underline\"][\"yellow\"]\n";
    cout << cli.color["bold"]["bgRed"]["white"]("Bold White on Red") << " - Use [\"bold\"][\"bgRed\"][\"white\"]\n";
    cout << cli.color["bold"]["underline"]["brightGreen"]("Bold Underlined Bright Green") << " - Use [\"bold\"][\"underline\"][\"brightGreen\"]\n";
}

int main(int argc, char* argv[]) {
    CLI cli = parseCLI(argc, argv);
    
    if (cli.noArgs)                  exit("Arguments needed. Try: --showcase or --help");
    if (cli.s["h"] || cli.c["help"]) exit(getHelpMenu(cli));
    if (cli.c["version"])            exit("V1.0.0");
    
    if (cli.c["showcase"]) {
        cout << "\n" << cli.color["bold"]["brightCyan"]("+=======================================+") << "\n";
        cout << cli.color["bold"]["brightCyan"]("|") << "     " 
             << cli.color["bold"]["white"]("CLI COLOR SYSTEM SHOWCASE") << "     " 
             << cli.color["bold"]["brightCyan"]("|") << "\n";
        cout << cli.color["bold"]["brightCyan"]("+=======================================+") << "\n\n";
        
        showStyles(cli);
        showColors(cli);
        showBrightColors(cli);
        showBackgrounds(cli);
        showCombinations(cli);
        
        cout << "\n" << cli.color["bold"]["underline"]("PRACTICAL EXAMPLES") << "\n\n";
        
        cout << cli.color["green"]("[OK]") << " " << cli.color["bold"]("Success:") 
             << " Operation completed successfully\n";
        cout << cli.color["red"]("[ERR]") << " " << cli.color["bold"]("Error:") 
             << " Something went wrong\n";
        cout << cli.color["yellow"]("[WARN]") << " " << cli.color["bold"]("Warning:") 
             << " Please review your input\n";
        cout << cli.color["blue"]("[INFO]") << " " << cli.color["bold"]("Info:") 
             << " Processing data...\n";
        cout << cli.color["cyan"]("[STEP]") << " " << cli.color["bold"]("Step 1:") 
             << " Initialize configuration\n";
        cout << cli.color["magenta"]("[DEBUG]") << " " << cli.color["bold"]("Debug:") << " " 
             << cli.color["dim"]("Variable x = 42") << "\n";
    }
    
    if (cli.c["styles"])       showStyles(cli);
    if (cli.c["colors"])       showColors(cli);
    if (cli.c["bright"])       showBrightColors(cli);
    if (cli.c["backgrounds"])  showBackgrounds(cli);
    if (cli.c["combinations"]) showCombinations(cli);
    
    if (cli.c["all"]) {
        showStyles(cli);
        showColors(cli);
        showBrightColors(cli);
        showBackgrounds(cli);
        showCombinations(cli);
    }
    
    return 0;
}
