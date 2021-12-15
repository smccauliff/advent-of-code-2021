#include <bingo.hpp>
#include <aoc-2021.hpp>
#include <vector>
#include <cstring>

using namespace aoc2021;
using namespace bingo;

int main(int argc, char** argv) {
  auto lines = ParseLinesFromFile(argv[1]);

  auto selected_numbers = ParseNumberSelections(lines[0], ',');

  std::vector<BBoard> boards;
  for (uint32_t line_index = 1; line_index < lines.size(); line_index += kBoardDim) {
    auto board = ParseBoard(lines.cbegin() + line_index, lines.cbegin() + kBoardDim);
    boards.emplace_back(std::move(board));
  }

  /*
  std::vector<BBoardMarkings> markings(boards.size());
  for (int i = 0; i < markings.size(); ++i) {
    memset(&boards[i], 0, sizeof(BBoardMarkings));
  }
*/
}