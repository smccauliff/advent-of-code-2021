#pragma once

#include <array>
#include <vector>

namespace bingo {

constexpr uint32_t kBoardDim = 5;

using BBoard = std::array<std::array<uint32_t, kBoardDim>, kBoardDim>;

using BBoardMarkings = std::array<<std::array<bool, kBoardDim>, kBoardDim>;

std::vector<uint32_t> ParseNumberSelections(const std::string& input);

BBoard ParseBoard(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end);

} //end namespace