#include <bingo.hpp>

#include <aoc-2021.hpp>
#include <charconv>
#include<boost/tokenizer.hpp>

using namespace boost;

namespace bingo {


template<typename CONVERTER, typename DELIMITER, typename ELEMENT>
std::vector<ELEMENT> ParseDelimitedList(const std::string& input, DELIMITER d, CONVERTER converter) {
  uint64_t start = 0;
  std::vector<ELEMENT> parsed_elements;
  while (true) {
    auto pos = input.find(d, start);
    uint64_t last_index = pos;
    if (pos == std::string::npos) {
      last_index = input.size();
    }
    ELEMENT value = converter(input.data() + start, input.data() + last_index);
    parsed_elements.push_back(value);
    if (pos == std::string::npos) {
      break;
    }
    start = pos + 1;
  }

  return parsed_elements;
}

template <typename CONVERTER, typename DELIMITER>
std::vector<uint32_t> ParseDelimitedUInt32List(const std::string& input, DELIMITER d, CONVERTER converter) {
  return ParseDelimitedList<CONVERTER, DELIMITER, uint32_t>(input, d, converter);
}

std::vector<uint32_t> ParseNumberSelections(const std::string& input, char delimiter) {
  return ParseDelimitedUInt32List(input, delimiter, [](const char* start, const char* end) {
    uint32_t value;
    auto from_chars_result = std::from_chars(start, end, value);
    ALWAYS_ASSERT(static_cast<uint64_t>(from_chars_result.ec) == 0);
    return value;
  });
}

BBoard ParseBoard(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end) {
  auto current = begin;
  BBoard board;
  uint32_t row = 0;
  while (current != end) {
    auto board_line = ParseNumberSelections(*current, ' ');
    std::copy(board_line.cbegin(), board_line.cend(), board[row++].begin());
  }
  return board;
}

} //end namespace