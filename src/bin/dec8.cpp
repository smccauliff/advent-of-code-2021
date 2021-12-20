#include <aoc-2021.hpp>
#include <iostream>
#include <boost/tokenizer.hpp>
#include <set>
#include <string>

using namespace aoc2021;

struct StringByLength {
    inline bool operator()(const std::string& a,  const std::string& b) const {
        return a.size() < b.size();
    }
};

struct WiresInDisplayOut {
  std::set<std::string, StringByLength> wires_on;
  std::vector<std::string> outputs;
};

std::ostream& operator<<(std::ostream& out, const struct WiresInDisplayOut& x) {
  for (const auto& w : x.wires_on) {
    std::cout << w << ",";
  }
  std::cout << "_";
  for (const auto& o : x.outputs) {
    std::cout << o << ",";
  }

  return out;
}

uint32_t NumberOfKnownSegmentsFound(const std::string& known, const std::string& unknown) {
  uint32_t found_count = 0;
  for (char k : known) {
    if (unknown.find(k) != std::string::npos) {
      ++found_count;
    }
  }
  return found_count;
}

uint32_t AssignDigit(const std::string& x, const WiresInDisplayOut& wido) {
  switch (x.size()) {
    case 2: return 1;
    case 3: return 7;
    case 4: return 4;
    case 7: return 8;
    case 5: // 2, 3, 5
    {
      // Is the 1 digit part of the shape?
      auto it = wido.wires_on.begin();
      if (NumberOfKnownSegmentsFound(*it, x) == 2) {
        return 3;
      } else {
        ++it;
        ++it; //4
        if (NumberOfKnownSegmentsFound(*it, x) == 3) {
          // The 5 digit is missing only one of the segments found in the 4
          return 5;
        } else {
          // The 2 digit is missing two of the segments that the 4 has
          return 2;
        }
      }
    }
      break;
    case 6: //0, 6, 9
    {
      auto it = wido.wires_on.begin();
      if (NumberOfKnownSegmentsFound(*it, x) == 1) {
        return 6;
      } else {
        ++it;
        ++it; // 4
        if (NumberOfKnownSegmentsFound(*it, x) == 4) {
          return 9;
        } else {
          return 0;
        }
      }
    }
    break;
    default:
      abort();
  }
}

/*
 aaaa    ....    aaaa    aaaa    ....
b    c  .    c  .    c  .    c  b    c
b    c  .    c  .    c  .    c  b    c
 ....    ....    dddd    dddd    dddd
e    f  .    f  e    .  .    f  .    f
e    f  .    f  e    .  .    f  .    f
 gggg    ....    gggg    gggg    ....

  5:      6:      7:      8:      9:
 aaaa    aaaa    aaaa    aaaa    aaaa
b    .  b    .  .    c  b    c  b    c
b    .  b    .  .    c  b    c  b    c
 dddd    dddd    ....    dddd    dddd
.    f  e    f  .    f  e    f  .    f
.    f  e    f  .    f  e    f  .    f
 gggg    gggg    ....    gggg    gggg

 */
int main(int argc, char** argv) {
  auto lines = ParseLinesFromFile(argv[1]);
  std::vector<WiresInDisplayOut> problem_inputs;
  for (const auto& line : lines) {
    boost::char_separator<char> pipe_sep{"|", ""};
    boost::tokenizer tokenizer_pipe(line, pipe_sep);
    struct WiresInDisplayOut wido;
    int32_t part_count = 0;
    for (auto token : tokenizer_pipe) {
      boost::tokenizer individual_segments(token);
      for (auto token2 : individual_segments) {
        switch (part_count) {
          case 0: wido.wires_on.insert(token2); break;
          case 1: wido.outputs.emplace_back(std::move(token2)); break;
          default:
            abort();
        }
      }
      ++part_count;
    }
    problem_inputs.emplace_back(std::move(wido));
  }

  uint64_t total_count = 0;
  for (const auto& wido : problem_inputs) {
    uint32_t display_value = 0;
    for (const auto& output : wido.outputs) {
      display_value *= 10;
      uint32_t digit = AssignDigit(output, wido);
      display_value += digit;
    }
    std::cout << "display value " << display_value << std::endl;
    total_count += display_value;
  }
  std::cout << "total value " << total_count << std::endl;
  exit(0);
}