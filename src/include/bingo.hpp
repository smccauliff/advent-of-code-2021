#pragma once

#include <array>
#include <vector>
#include <cstdint>
#include <string>
#include <optional>
#include <set>

namespace bingo {

constexpr uint32_t kBoardDim = 5;

using BBoard = std::array<std::array<uint32_t, kBoardDim>, kBoardDim>;

std::vector<uint32_t> ParseNumberSelections(const std::string& input);

BBoard ParseBoard(std::vector<std::string>::const_iterator begin, std::vector<std::string>::const_iterator end);

std::optional<uint32_t> EvaluateBoard(const BBoard& bboard, const std::set<uint32_t>& chosen);

} //end namespace