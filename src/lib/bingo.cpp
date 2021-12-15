#include <bingo.hpp>

#include <aoc-2021.hpp>
#include <charconv>
#include <boost/tokenizer.hpp>

namespace bingo {


std::vector<uint32_t> ParseNumberSelections(const std::string& input) {
  std::vector<uint32_t> rv;
  boost::tokenizer<> toker(input);
  for (const auto& token : toker) {
    uint32_t value;
    auto from_chars_result = std::from_chars(token.data(), token.data() + token.length(), value);
    ALWAYS_ASSERT(static_cast<uint64_t>(from_chars_result.ec) == 0);
    rv.push_back(value);
  }

  return rv;
}

BBoard ParseBoard(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end) {
  auto current = begin;
  BBoard board;
  uint32_t row = 0;
  while (current != end) {
    std::vector<uint32_t> rv;
    boost::tokenizer<> toker(*current);
    uint32_t col = 0;
    for (const auto& token : toker) {
      auto from_chars_result = std::from_chars(token.data(), token.data() + token.length(), board[row][col++]);
      ALWAYS_ASSERT(static_cast<uint64_t>(from_chars_result.ec) == 0);
    }
    ALWAYS_ASSERT(col == kBoardDim)
    ++row;
    ++current;
  }
  ALWAYS_ASSERT(row == kBoardDim);
  return board;
}


static uint32_t EvaluateMissing(const BBoard& bboard, const std::set<uint32_t>& chosen) {
  uint32_t sum = 0;
  for (uint32_t row = 0; row < kBoardDim; ++row) {
    for (uint32_t col = 0; col < kBoardDim; ++col) {
      if (chosen.find(bboard[row][col]) == chosen.end()) {
        sum += bboard[row][col];
      }
    }
  }
  return sum;
}

std::optional<uint32_t> EvaluateBoard(const BBoard& bboard, const std::set<uint32_t>& chosen) {
  for (uint32_t row = 0; row < kBoardDim; ++row) {
    uint32_t col;
    for (col = 0; col < kBoardDim; ++col) {
      if (chosen.find(bboard[row][col]) == chosen.end()) {
        break;
      }
    }
    if (col == kBoardDim) {
      return EvaluateMissing(bboard, chosen);
    }
  }

  for (uint32_t col = 0; col < kBoardDim; ++col) {
    uint32_t row;
    for (row = 0; row < kBoardDim; ++row) {
      if (chosen.find(bboard[row][col]) == chosen.end()) {
        break;
      }
    }
    if (row == kBoardDim) {
      return EvaluateMissing(bboard, chosen);
    }
  }

  return {};
}

} //end namespace