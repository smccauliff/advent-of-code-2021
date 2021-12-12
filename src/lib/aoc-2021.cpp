#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <aoc-2021.hpp>
#include <numeric>
#include <algorithm>
#include <cmath>

namespace aoc2021 {

std::vector<std::string> ParseLinesFromFile(const std::string& fname) {
  std::ifstream in(fname, std::ios::binary);
  ALWAYS_ASSERT(in.good());

  std::vector<std::string> strings_from_file;
  while (true) {
    {
      std::string line;
      std::getline(in, line);
      if (!line.empty()) {
        strings_from_file.emplace_back(std::move(line));
      }
    }
    if (in.eof()) {
      break;
    }
    ALWAYS_ASSERT(in.good());
  }

  return strings_from_file;
}


LifeSupportComputer::LifeSupportComputer(std::vector<std::string>& inputs) {
    readings_.reserve(inputs.size());
    single_reading_length_ =0 ;
    std::for_each(inputs.begin(), inputs.end(), [&](const std::string& line) {
      if (readings_.empty()) {
        single_reading_length_ = line.size();
      }
      std::vector<uint8_t> reading;
      reading.reserve(single_reading_length_);
      std::for_each(line.begin(), line.end(), [&](const char c) {
        switch (c) {
          case '0': reading.push_back(0); break;
          case '1': reading.push_back(1); break;
          default:
            std::abort();
        }
      });

      readings_.emplace_back(std::move(reading));
    });
}

uint32_t LifeSupportComputer::LifeSupportReadings() {
  return FindReading(true) * FindReading(false);
}

uint32_t LifeSupportComputer::FindReading(bool majority_bit)  {
    std::list<std::vector<uint8_t>*> current;
    std::for_each(readings_.begin(), readings_.end(), [&current](const std::vector<uint8_t>& x) { current.push_back(const_cast<std::vector<uint8_t>*>(&x)); });
    for (uint32_t i = 0 ; i < single_reading_length_ && current.size() > 1; i++) {
      auto sum = SumAt(i, current);
      //std::cout << "sum at : " << i << " " << sum << " "  << std::endl;
      auto keep_ones =  (majority_bit) ? sum >= (current.size() - sum) : sum < (current.size() - sum);
      current.remove_if([keep_ones, i](const auto& v) {
        return (!keep_ones && (*v)[i] == 1) || (keep_ones && (*v)[i] == 0);
      });
    }

    ALWAYS_ASSERT(current.size() == 1);

    uint32_t ans = 0;
    const auto& vector_ans = **current.begin();
    for (uint32_t i = 0; i < single_reading_length_; i++) {
      if (vector_ans[i]) {
        ans |= 1;
      }
      ans = ans << 1;
    }
    ans = ans >> 1;
    std::cout << "ans " << ans << std::endl;
    return ans;
}

uint32_t LifeSupportComputer::SumAt(uint32_t bit_index, const std::list<std::vector<uint8_t>*>& v) {
    return std::accumulate(v.begin(), v.end(), 0, [bit_index](uint64_t count, const std::vector<uint8_t>* reading) {
      if ((*reading)[bit_index]) {
        return count + 1;
      }
      return count;
    });
}


} //end namespace
