#include <aoc-2021.hpp>
#include <iostream>
#include <array>
#include <numeric>
#include <boost/multiprecision/cpp_int.hpp>

using namespace aoc2021;

int main(int argc, char** argv) {

  auto lines = ParseLinesFromFile(argv[1]);
  auto selected_numbers = ParseNumbers(lines[0]);

  std::array<boost::multiprecision::uint128_t , 9> fish_counts;
  fish_counts.fill(0);

  for (auto day_count : selected_numbers) {
    fish_counts[day_count]++;
  }

  // This could be done without shifting.
  for (uint32_t day = 0; day < 256; day++) {
    boost::multiprecision::uint128_t zero_counts = fish_counts[0];
    for (uint32_t i = 1; i < fish_counts.size(); i++) {
      fish_counts[i - 1] = fish_counts[i];
    }
    // new fish
    fish_counts[fish_counts.size() - 1] = zero_counts;
    // just reproducing fish
    fish_counts[6] += zero_counts;
  }

  auto sum = std::accumulate(fish_counts.begin(), fish_counts.end(),  static_cast<boost::multiprecision::uint128_t>(0),
                             [](auto s, auto c) { return s + c; } );
  std::cout << "sum " << sum << std::endl;
}