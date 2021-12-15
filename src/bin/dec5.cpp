#include <aoc-2021.hpp>
#include <iostream>
#include <charconv>
#include <boost/tokenizer.hpp>

using namespace aoc2021;

int main(int argc, char** argv) {
  //This is the terrible brute force way of doing this.

  auto lines = ParseLinesFromFile(argv[1]);

  std::vector<std::array<uint16_t, 4>> coordinates;
  for (const auto& line : lines) {
    std::array<uint16_t, 4> coordinate;
    boost::tokenizer<> toker(line);
    uint32_t i = 0;
    for (const auto& token : toker) {
      auto from_chars_result = std::from_chars(token.data(), token.data() + token.length(), coordinate[i]);
      ALWAYS_ASSERT(static_cast<uint64_t>(from_chars_result.ec) == 0);
      i++;
    }

    coordinates.emplace_back(std::move(coordinate));

  }

  uint16_t max_x = 0;
  uint16_t max_y = 0;
  for (const auto& coordinate : coordinates) {
    if (coordinate[0] > max_x) {
      max_x = coordinate[0];
    }
    if (coordinate[1] > max_y) {
      max_y = coordinate[1];
    }
    if (coordinate[2] > max_x) {
      max_x = coordinate[2];
    }
    if (coordinate[3] > max_y) {
      max_y = coordinate[3];
    }
  }

  std::vector<std::vector<uint16_t>> ocean_floor;
  std::vector<uint16_t> initial_counts;
  initial_counts.resize(max_x + 1, 0);
  ocean_floor.resize(max_y + 1, initial_counts);

  for (const auto& coordinate : coordinates) {
    if (coordinate[0] == coordinate[2]) {
      for (uint16_t row = coordinate[1]; row <= coordinate[3]; ++row) {
        ocean_floor[row][coordinate[0]]++;
      }
    } else {
      for (uint16_t col = coordinate[0]; col <= coordinate[2]; ++col) {
        ocean_floor[coordinate[1]][col]++;
      }
    }
  }

  uint32_t total = 0;
  for (auto v : ocean_floor) {
    for (auto count : v) {
      if (count >= 2) {
        total++;
      }
    }
  }

  // wrong: 5465
  std::cout << "Total intersections " << total << std::endl;

}