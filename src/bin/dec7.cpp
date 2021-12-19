#include <aoc-2021.hpp>
#include <iostream>
#include <numeric>
#include <unordered_map>

using namespace aoc2021;

int64_t CrabFuelCost(int64_t from, int64_t to) {
  static std::unordered_map<int64_t, int64_t> cost_cache;
  auto position_difference = std::abs(from - to);
  auto it = cost_cache.find(position_difference);
  if (it != cost_cache.end()) {
    return it->second;
  }

  /// could get upper bound from ordered map to avoid recomputation.
  int64_t cost = 0;
  for (int64_t i = 0; i < position_difference; i++) {
    cost += i;
    cost_cache[i] = cost;
  }
  return cost;
}

int main(int argc, char** argv) {

  auto lines = ParseLinesFromFile(argv[1]);
  auto selected_numbers = ParseNumbers(lines[0]);

  auto max_position = std::accumulate(selected_numbers.begin(), selected_numbers.end(),
                                      static_cast<int64_t>(0), [](auto s, int64_t c) {
    return std::max(s, c);
  });

  std::vector<int64_t> positions;
  positions.resize(max_position + 1, 0);

  for (auto position : selected_numbers) {
    positions[position]++;
  }

  std::vector<int64_t> cost_matrix;
  cost_matrix.resize(positions.size(), 0);

  for (int64_t to = 0; to < positions.size(); ++to) {
    for (int64_t from = 0; from < positions.size(); ++from) {
      cost_matrix[to] += CrabFuelCost(from, to) * static_cast<int64_t>(positions[from]);
    }
  }

  int64_t min_cost = std::numeric_limits<int64_t>::max();
  int64_t min_cost_position = -1;
  for (int64_t i = 0; i < cost_matrix.size(); ++i) {
    std::cout << cost_matrix[i]  << ",";
    if (min_cost > cost_matrix[i]) {
      min_cost = cost_matrix[i];
      min_cost_position = i;
    }
  }
  std::cout << std::endl;

  // wrong answer : 353
  std::cout << "min cost position (add one to this for the aoc answer) "
    << min_cost_position << " min cost " << min_cost << std::endl;

}