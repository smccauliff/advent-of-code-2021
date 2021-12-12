#pragma  once

#include <cstdlib>
#include <vector>
#include <string>

#define ALWAYS_ASSERT(TEST) \
  if (!(TEST)) {            \
    std::abort();           \
  }

namespace aoc2021 {

std::vector<std::string> ParseLinesFromFile(const std::string& fname);

} // end namespace