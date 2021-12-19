#pragma  once

#include <cstdlib>
#include <vector>
#include <string>
#include <list>
#include <numeric>

#define ALWAYS_ASSERT(TEST) \
  if (!(TEST)) {            \
    std::abort();           \
  }

namespace aoc2021 {

template<typename Container, typename Sum, typename ContainedType, typename BinaryOperation>
Sum AccumulateContainer(const Container& container, Sum initial_value, BinaryOperation binary_operation) {
  return std::accumulate(container.begin(), container.end(), initial_value, binary_operation);
}


std::vector<std::string> ParseLinesFromFile(const std::string& fname);


std::vector<uint32_t> ParseNumbers(const std::string& input);

class LifeSupportComputer {
 public:
  LifeSupportComputer(std::vector<std::string>& inputs);


  uint32_t LifeSupportReadings();

 private:

  uint32_t FindReading(bool majority_bit);

  static uint32_t SumAt(uint32_t bit_index, const std::list<std::vector<uint8_t>*>& v);

  std::vector<std::vector<uint8_t>> readings_;
  uint32_t single_reading_length_;
};

} // end namespace