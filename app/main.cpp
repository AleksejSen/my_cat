#include "CLI/CLI.hpp"
#include <filesystem>
#include <fmt/base.h>
#include <fmt/ranges.h>
#include <fstream>
#include <iostream>
#include <vector>

namespace Color {
  // ANSI escape codes for colors
  const std::string reset("\033[0m");
  const std::string red("\033[0;31m");           // Red
  const std::string green("\033[1;32m");         // Green
  const std::string yellow("\033[1;33m");        // Yellow
  const std::string blue("\033[1;34m");          // Blue
  const std::string magenta("\033[0;35m");       // Magenta
  const std::string cyan("\033[0;36m");          // Cyan
  const std::string white("\033[1;37m");         // White
} // namespace Color

const std::string bracesColor = Color::cyan;
const std::string curlyBracesColor = Color::yellow;
const std::string squareBracesColor = Color::red;
const std::string punctuationColor = Color::green;
const std::string textColor = Color::white;
const std::string quotesColor = Color::blue;

std::vector<std::string>
readFilesToVector(const std::filesystem::path &filePath) {
  std::vector<std::string> lines;

  std::ifstream file(filePath);

  if (!file.is_open()) {
    std::cerr << "Erro opening file:" << filePath << std::endl;
    return lines;
  }

  std::string line;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }

  return lines;
}

void outputLines(std::vector<std::string> lines, bool printLineNr) {
  if (printLineNr) {
    int line_nr = 1;
    for (auto &&line : lines) {
      // Line Numbers
      fmt::print("{}{}|", Color::cyan, line_nr);

      // Print with fancy coloring
      for (auto &&ch : line) {
        switch (ch) {
        case '.':
        case ',':
        case ':':
        case ';':
          fmt::print("{}{}{}", punctuationColor, ch, Color::reset);
          break;
        case '{':
        case '}':
          fmt::print("{}{}{}", curlyBracesColor, ch, Color::reset);
          break;
        case '[':
        case ']':
          fmt::print("{}{}{}", squareBracesColor, ch, Color::reset);
          break;
        case '(':
        case ')':
          fmt::print("{}{}{}", bracesColor, ch, Color::reset);
          break;
        case '"':
          fmt::print("{}{}{}", quotesColor, ch, Color::reset);
          break;
        default:
          fmt::print("{}{}{}", textColor, ch, Color::reset);
          break;
        }
      }

      // Reset Colors
      fmt::print("{}\n", Color::reset);
      ++line_nr;
    }
  } else {
    for (auto &&line : lines) {
      fmt::print("{} \n", line);
    }
  }
}

int main(int argc, char **argv) {
  CLI::App app{"App description"};

  // Define options
  bool lines_flage{false};
  bool verbose{false};
  app.add_flag("-l", lines_flage, "lines");
  app.add_flag("-v", verbose, "verbose");

  // Add a positional argument for the file path
  std::string filePathString;
  app.add_option("file", filePathString, "Path to the file")->required();

  CLI11_PARSE(app, argc, argv);

  std::filesystem::path filePath{filePathString};

  if (verbose) {
    fmt::print("Line Numbes:{}\n", lines_flage);
    fmt::print("Verbose:{}\n", verbose);
    std::filesystem::path absolutePath = std::filesystem::absolute(filePath);
    fmt::print("File Path:{}\n", absolutePath.string());
  }

  if (std::filesystem::exists(filePath)) {
    // Do the work:
    outputLines(readFilesToVector(filePath), lines_flage);

  } else {
    fmt::print("No such file:{}\n", filePath.string());
  }

  return 0;
}
