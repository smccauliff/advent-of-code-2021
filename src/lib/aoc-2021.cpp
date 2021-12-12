#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <aoc-2021.hpp>

namespace aoc2021 {
std::vector<std::string> ParseLinesFromFile(const std::string& fname) {
  std::ifstream in(fname, std::ios::binary);
  ALWAYS_ASSERT(in.good());

  std::vector<std::string> strings_from_file;
  while (true) {
    {
      std::string line;
      std::getline(in, line);
      strings_from_file.emplace_back(std::move(line));
    }
    if (in.eof()) {
      break;
    }
    ALWAYS_ASSERT(in.good());
  }

  return strings_from_file;
}
} //end namespace
