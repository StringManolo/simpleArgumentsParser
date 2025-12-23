#ifndef SIMPLEARGUMENTSPARSER_HPP
#define SIMPLEARGUMENTSPARSER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <regex>
#include <variant>
#include <iomanip>
#include <cstring>
#include <cstdio>

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <unistd.h>
#endif

namespace ANSI {
  constexpr const char* RESET = "\033[0m";
  constexpr const char* BOLD = "\033[1m";
  constexpr const char* DIM = "\033[2m";
  constexpr const char* ITALIC = "\033[3m";
  constexpr const char* UNDERLINE = "\033[4m";
  constexpr const char* BLINK = "\033[5m";
  constexpr const char* INVERT = "\033[7m";
  constexpr const char* BLACK = "\033[30m";
  constexpr const char* RED = "\033[31m";
  constexpr const char* GREEN = "\033[32m";
  constexpr const char* YELLOW = "\033[33m";
  constexpr const char* BLUE = "\033[34m";
  constexpr const char* MAGENTA = "\033[35m";
  constexpr const char* CYAN = "\033[36m";
  constexpr const char* WHITE = "\033[37m";
  constexpr const char* BRIGHT_BLACK = "\033[90m";
  constexpr const char* BRIGHT_RED = "\033[91m";
  constexpr const char* BRIGHT_GREEN = "\033[92m";
  constexpr const char* BRIGHT_YELLOW = "\033[93m";
  constexpr const char* BRIGHT_BLUE = "\033[94m";
  constexpr const char* BRIGHT_MAGENTA = "\033[95m";
  constexpr const char* BRIGHT_CYAN = "\033[96m";
  constexpr const char* BRIGHT_WHITE = "\033[97m";
  constexpr const char* BG_BLACK = "\033[40m";
  constexpr const char* BG_RED = "\033[41m";
  constexpr const char* BG_GREEN = "\033[42m";
  constexpr const char* BG_YELLOW = "\033[43m";
  constexpr const char* BG_BLUE = "\033[44m";
  constexpr const char* BG_MAGENTA = "\033[45m";
  constexpr const char* BG_CYAN = "\033[46m";
  constexpr const char* BG_WHITE = "\033[47m";
}

class JSValue {
  private:
    std::variant<std::string, bool> value;
    bool exists;

  public:
    JSValue() : value(std::string("")), exists(false) {}
    JSValue(const char* s) : value(std::string(s)), exists(true) {}
    JSValue(const std::string& s) : value(s), exists(true) {}
    JSValue(bool b) : value(b), exists(true) {}

    operator bool() const {
      if (!exists) return false;
      if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value);
      } else {
        std::string s = std::get<std::string>(value);
        return !s.empty() && s != "false" && s != "0";
      }
    }

    std::string toString() const {
      if (!exists) return "";
      if (std::holds_alternative<std::string>(value)) {
        return std::get<std::string>(value);
      } else {
        return std::get<bool>(value) ? "true" : "false";
      }
    }

    bool isString() const { return exists && std::holds_alternative<std::string>(value); }
    bool isBool() const { return exists && std::holds_alternative<bool>(value); }
    bool existsValue() const { return exists; }

    JSValue& operator=(const std::string& val) {
      value = val;
      exists = true;
      return *this;
    }

    JSValue& operator=(const char* val) {
      value = std::string(val);
      exists = true;
      return *this;
    }

    JSValue& operator=(bool val) {
      value = val;
      exists = true;
      return *this;
    }

    JSValue& operator=(int val) {
      value = (val != 0);
      exists = true;
      return *this;
    }
};

class JSMap {
  private:
    std::unordered_map<std::string, JSValue> data;

  public:
    JSValue& operator[](const std::string& key) {
      return data[key];
    }

    JSValue operator[](const std::string& key) const {
      auto it = data.find(key);
      if (it != data.end()) return it->second;
      return JSValue();
    }

    bool has(const std::string& key) const {
      return data.find(key) != data.end();
    }

    std::vector<std::string> keys() const {
      std::vector<std::string> result;
      for (const auto& pair : data) {
        result.push_back(pair.first);
      }
      return result;
    }

    size_t size() const {
      return data.size();
    }

    bool empty() const {
      return data.empty();
    }
};

class Color {
  private:
    std::string codes;

    Color(const std::string& c, bool) : codes(c) {} 

  public:
    Color() : codes("") {}
    Color(const std::string& c) : codes(c) {}

    std::string operator()(const std::string& text) const {
      return codes + text + ANSI::RESET;
    }

    std::string operator()(const char* text) const {
      return codes + std::string(text) + ANSI::RESET;
    }

    Color bold() const { return Color(codes + ANSI::BOLD, true); }
    Color dim() const { return Color(codes + ANSI::DIM, true); }
    Color italic() const { return Color(codes + ANSI::ITALIC, true); }
    Color underline() const { return Color(codes + ANSI::UNDERLINE, true); }
    Color blink() const { return Color(codes + ANSI::BLINK, true); }
    Color invert() const { return Color(codes + ANSI::INVERT, true); }

    Color black() const { return Color(codes + ANSI::BLACK, true); }
    Color red() const { return Color(codes + ANSI::RED, true); }
    Color green() const { return Color(codes + ANSI::GREEN, true); }
    Color yellow() const { return Color(codes + ANSI::YELLOW, true); }
    Color blue() const { return Color(codes + ANSI::BLUE, true); }
    Color magenta() const { return Color(codes + ANSI::MAGENTA, true); }
    Color cyan() const { return Color(codes + ANSI::CYAN, true); }
    Color white() const { return Color(codes + ANSI::WHITE, true); }

    Color brightBlack() const { return Color(codes + ANSI::BRIGHT_BLACK, true); }
    Color brightRed() const { return Color(codes + ANSI::BRIGHT_RED, true); }
    Color brightGreen() const { return Color(codes + ANSI::BRIGHT_GREEN, true); }
    Color brightYellow() const { return Color(codes + ANSI::BRIGHT_YELLOW, true); }
    Color brightBlue() const { return Color(codes + ANSI::BRIGHT_BLUE, true); }
    Color brightMagenta() const { return Color(codes + ANSI::BRIGHT_MAGENTA, true); }
    Color brightCyan() const { return Color(codes + ANSI::BRIGHT_CYAN, true); }
    Color brightWhite() const { return Color(codes + ANSI::BRIGHT_WHITE, true); }

    Color bgBlack() const { return Color(codes + ANSI::BG_BLACK, true); }
    Color bgRed() const { return Color(codes + ANSI::BG_RED, true); }
    Color bgGreen() const { return Color(codes + ANSI::BG_GREEN, true); }
    Color bgYellow() const { return Color(codes + ANSI::BG_YELLOW, true); }
    Color bgBlue() const { return Color(codes + ANSI::BG_BLUE, true); }
    Color bgMagenta() const { return Color(codes + ANSI::BG_MAGENTA, true); }
    Color bgCyan() const { return Color(codes + ANSI::BG_CYAN, true); }
    Color bgWhite() const { return Color(codes + ANSI::BG_WHITE, true); }

    Color operator[](const std::string& name) const {
      static std::unordered_map<std::string, std::string> colorMap = {
        {"bold", ANSI::BOLD}, {"dim", ANSI::DIM}, {"italic", ANSI::ITALIC},
        {"underline", ANSI::UNDERLINE}, {"blink", ANSI::BLINK}, {"invert", ANSI::INVERT},
        {"black", ANSI::BLACK}, {"red", ANSI::RED}, {"green", ANSI::GREEN},
        {"yellow", ANSI::YELLOW}, {"blue", ANSI::BLUE}, {"magenta", ANSI::MAGENTA},
        {"cyan", ANSI::CYAN}, {"white", ANSI::WHITE},
        {"brightBlack", ANSI::BRIGHT_BLACK}, {"brightRed", ANSI::BRIGHT_RED},
        {"brightGreen", ANSI::BRIGHT_GREEN}, {"brightYellow", ANSI::BRIGHT_YELLOW},
        {"brightBlue", ANSI::BRIGHT_BLUE}, {"brightMagenta", ANSI::BRIGHT_MAGENTA},
        {"brightCyan", ANSI::BRIGHT_CYAN}, {"brightWhite", ANSI::BRIGHT_WHITE},
        {"bgBlack", ANSI::BG_BLACK}, {"bgRed", ANSI::BG_RED}, {"bgGreen", ANSI::BG_GREEN},
        {"bgYellow", ANSI::BG_YELLOW}, {"bgBlue", ANSI::BG_BLUE}, {"bgMagenta", ANSI::BG_MAGENTA},
        {"bgCyan", ANSI::BG_CYAN}, {"bgWhite", ANSI::BG_WHITE}
      };

      std::string key = name;
      std::transform(key.begin(), key.end(), key.begin(), ::tolower);

      if (key.find("bright") == 0 && key.length() > 6) {
        std::string color = key.substr(6);
        color[0] = std::toupper(color[0]);
        key = "bright" + color;
      } else if (key.find("bg") == 0 && key.length() > 2) {
        std::string color = key.substr(2);
        color[0] = std::toupper(color[0]);
        key = "bg" + color;
      }

      auto it = colorMap.find(key);
      if (it != colorMap.end()) {
        return Color(codes + it->second, true);
      }
      return Color(codes, true);
    }
};

class CLI {
  private:
    JSMap s_obj;
    JSMap c_obj;
    std::vector<std::pair<std::string, int>> o_vec;
    std::string p_str;
    std::vector<int> e_vec;
    bool noArgs_bool;
    int argc_int;

    static std::string getPippedInput() {
      std::string input;
#ifdef _WIN32
      if (!_isatty(_fileno(stdin))) {
#else
        if (!isatty(STDIN_FILENO)) {
#endif
          std::string line;
          while (std::getline(std::cin, line)) {
            input += line + "\n";
          }
          if (!input.empty() && input.back() == '\n') {
            input.pop_back();
          }
        }
        return input;
      }

      static bool isValidLongArg(const std::string& arg) {
        static std::regex pattern("^[a-zA-Z0-9]+(?:-[a-zA-Z0-9]+)*$");
        return std::regex_match(arg, pattern);
      }

      static bool isValidShortArg(const std::string& arg) {
        return !arg.empty() && std::all_of(arg.begin(), arg.end(), ::isalpha);
      }

      static std::string escapeJSON(const std::string& str) {
        std::string result;
        for (char c : str) {
          switch (c) {
            case '"': result += "\\\""; break;
            case '\\': result += "\\\\"; break;
            case '\b': result += "\\b"; break;
            case '\f': result += "\\f"; break;
            case '\n': result += "\\n"; break;
            case '\r': result += "\\r"; break;
            case '\t': result += "\\t"; break;
            default:
                       if (c >= 0 && c <= 0x1f) {
                         char buf[7];
                         snprintf(buf, sizeof(buf), "\\u%04x", static_cast<unsigned char>(c));
                         result += buf;
                       } else {
                         result += c;
                       }
          }
        }
        return result;
      }

      static bool tryJQ(const std::string& json) {
#ifndef _WIN32
        FILE* pipe = popen("which jq > /dev/null 2>&1 && echo 'found'", "r");
        if (pipe) {
          char buffer[128];
          bool hasJQ = false;
          while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            if (strstr(buffer, "found") != nullptr) {
              hasJQ = true;
            }
          }
          pclose(pipe);

          if (hasJQ) {
            std::string cmd = "echo '" + json + "' | jq .";
            pipe = popen(cmd.c_str(), "r");
            if (pipe) {
              std::cout << std::endl;
              while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
                std::cout << buffer;
              }
              pclose(pipe);
              return true;
            }
          }
        }
#endif
        return false;
      }

      public:
      JSMap s;
      JSMap c;
      std::vector<std::pair<std::string, int>> o;
      std::string p;
      std::vector<int> e;
      bool noArgs;
      int argc;
      Color color;

      CLI() : s(s_obj), c(c_obj), noArgs(false), argc(0), color("") {}

      static CLI parse(int argc, char* argv[]) {
        CLI cli;
        cli.argc = argc - 1;

        cli.p = getPippedInput();

        bool previousIsArg = false;

        for (int i = 1; i < argc; i++) {
          if (previousIsArg) {
            previousIsArg = false;
            continue;
          }

          std::string current = argv[i];
          std::string next = (i + 1 < argc) ? argv[i + 1] : "";

          if (!current.empty() && current[0] == '-') {
            if (current.size() > 1 && current[1] == '-') {
              // Argumento largo (--xxx)
              if (current.size() > 2) {
                std::string name = current.substr(2);

                if (isValidLongArg(name)) {
                  if (!next.empty() && (next[0] == '-' || 
                        (next.size() > 1 && next[0] == '-' && next[1] == '-'))) {
                    cli.c[name] = true;
                  } else {
                    if (next.empty()) {
                      cli.c[name] = true;
                    } else {
                      cli.c[name] = next;
                    }
                    previousIsArg = !next.empty();
                  }
                } else {
                  cli.o_vec.push_back({current, i + 1});
                }
              } else {
                cli.e_vec.push_back(i + 1);
              }
            } else {
              // Argumento corto (-x)
              if (current.size() > 1) {
                std::string name = current.substr(1);

                if (isValidShortArg(name)) {
                  if (!next.empty() && (next[0] == '-' || 
                        (next.size() > 1 && next[0] == '-' && next[1] == '-'))) {
                    cli.s[name] = true;
                  } else {
                    if (name.size() > 1) {
                      // Múltiples banderas: -xyz
                      for (char flag : name) {
                        cli.s[std::string(1, flag)] = true;
                      }
                    } else {
                      if (next.empty()) {
                        cli.s[name] = true;
                      } else {
                        cli.s[name] = next;
                      }
                      previousIsArg = !next.empty();
                    }
                  }
                } else {
                  cli.o_vec.push_back({current, i + 1});
                }
              }
            }
          } else {
            cli.o_vec.push_back({current, i + 1});
          }
        }

        cli.o = cli.o_vec;
        cli.e = cli.e_vec;

        if (cli.p.empty() && cli.argc == 0) {
          cli.noArgs = true;
        }

        return cli;
      }

      std::string toJSON(int indent = 2, bool tryUseJQ = false) const {
        std::stringstream ss;
        std::string spaces(indent, ' ');

        ss << "{\n";

        ss << spaces << "\"s\": {";
        auto sKeys = s.keys();
        for (size_t i = 0; i < sKeys.size(); i++) {
          if (i > 0) ss << ", ";
          std::string key = sKeys[i];
          std::string value = s[key].toString();
          ss << "\"" << escapeJSON(key) << "\": ";
          if (s[key].isBool()) {
            ss << (value == "true" ? "true" : "false");
          } else {
            ss << "\"" << escapeJSON(value) << "\"";
          }
        }
        ss << "},\n";

        ss << spaces << "\"c\": {";
        auto cKeys = c.keys();
        for (size_t i = 0; i < cKeys.size(); i++) {
          if (i > 0) ss << ", ";
          std::string key = cKeys[i];
          std::string value = c[key].toString();
          ss << "\"" << escapeJSON(key) << "\": ";
          if (c[key].isBool()) {
            ss << (value == "true" ? "true" : "false");
          } else {
            ss << "\"" << escapeJSON(value) << "\"";
          }
        }
        ss << "},\n";

        ss << spaces << "\"o\": [";
        for (size_t i = 0; i < o.size(); i++) {
          if (i > 0) ss << ", ";
          ss << "[\"" << escapeJSON(o[i].first) << "\", " << o[i].second << "]";
        }
        ss << "],\n";

        ss << spaces << "\"p\": ";
        if (p.empty()) {
          ss << "false";
        } else {
          ss << "\"" << escapeJSON(p) << "\"";
        }
        ss << ",\n";

        ss << spaces << "\"e\": [";
        for (size_t i = 0; i < e.size(); i++) {
          if (i > 0) ss << ", ";
          ss << e[i];
        }
        ss << "],\n";

        ss << spaces << "\"noArgs\": " << (noArgs ? "true" : "false") << ",\n";

        ss << spaces << "\"argc\": " << argc << "\n";

        ss << "}";

        std::string json = ss.str();

        if (tryUseJQ && tryJQ(json)) {
          return "";
        }

        return json;
      }

      void debug() const {
        std::cout << "CLI Debug:\n";
        std::cout << "  Short args (-x): ";
        for (const auto& key : s.keys()) {
          std::cout << "-" << key << "=" << s[key].toString() << " ";
        }
        std::cout << "\n  Long args (--xxx): ";
        for (const auto& key : c.keys()) {
          std::cout << "--" << key << "=" << c[key].toString() << " ";
        }
        std::cout << "\n  Other args: ";
        for (const auto& item : o) {
          std::cout << item.first << "(pos:" << item.second << ") ";
        }
        std::cout << "\n  Piped input: " << (p.empty() ? "none" : p.substr(0, 50) + (p.length() > 50 ? "..." : ""));
        std::cout << "\n  No args: " << (noArgs ? "true" : "false");
        std::cout << "\n  Arg count: " << argc << std::endl;
      }

      bool has(const std::string& shortName) const {
        return s.has(shortName);
      }

      bool hasLong(const std::string& longName) const {
        return c.has(longName);
      }

      std::string get(const std::string& shortName, const std::string& defaultValue = "") const {
        JSValue val = s[shortName];
        if (!val.existsValue()) return defaultValue;
        return val.toString();
      }

      std::string getLong(const std::string& longName, const std::string& defaultValue = "") const {
        JSValue val = c[longName];
        if (!val.existsValue()) return defaultValue;
        return val.toString();
      }

      bool isTrue(const std::string& shortName) const {
        JSValue val = s[shortName];
        if (!val.existsValue()) return false;
        return static_cast<bool>(val);
      }

      bool isLongTrue(const std::string& longName) const {
        JSValue val = c[longName];
        if (!val.existsValue()) return false;
        return static_cast<bool>(val);
      }
    };

    inline CLI parseCLI(int argc, char* argv[]) {
      return CLI::parse(argc, argv);
    }

    extern Color color;

#define CLI_OPT(obj, key) ((obj).has(key) ? (obj)[key] : JSValue())

#define CLI_DEBUG(cli) \
    std::cout << "DEBUG: argc=" << (cli).argc \
    << ", noArgs=" << ((cli).noArgs ? "true" : "false") \
    << ", piped=" << ((cli).p.empty() ? "false" : "\"" + (cli).p.substr(0, 20) + "...\"") \
    << std::endl

#endif 
