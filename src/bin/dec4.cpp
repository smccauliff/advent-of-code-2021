#include <bingo.hpp>
#include <aoc-2021.hpp>
#include <vector>
#include <iostream>

using namespace aoc2021;
using namespace bingo;

int main(int argc, char** argv) {
  auto lines = ParseLinesFromFile(argv[1]);

  auto selected_numbers = ParseNumbers(lines[0]);

  std::list<BBoard> boards;
  for (uint32_t line_index = 1; line_index < lines.size(); line_index += kBoardDim) {
    auto board = ParseBoard(lines.cbegin() + line_index, lines.cbegin() + + line_index + kBoardDim);
    boards.emplace_back(std::move(board));
  }

  // first: winning board 25023
  // last:
  std::set<uint32_t> current_selection;
  for (uint32_t next_selection : selected_numbers) {
    if (boards.empty()) {
      exit(0);
    }
    current_selection.insert(next_selection);
    //std::cout << "next_selection " << next_selection << std::endl;
    for (auto it = boards.begin(); it != boards.end();) {
      auto opt = EvaluateBoard(*it, current_selection);
      if (opt) {
        uint32_t board_score = *opt * next_selection;
        std::cout << "winning board " << board_score << std::endl;
        it = boards.erase(it);
      } else {
        ++it;
      }
      //std::cout << "boards remaining " << boards.size() << std::endl;
    }
  }
}