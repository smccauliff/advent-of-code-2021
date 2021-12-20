#include <aoc-2021.hpp>
#include <iostream>
#include <functional>
#include <utility>
#include <set>
#include <list>

using namespace aoc2021;

void FindLowPoints(uint32_t row_count, uint32_t col_count,
                   const std::vector<std::vector<uint32_t>>& height_map,
                   std::function<void(uint32_t, uint32_t)> visit_low_point) {

  // upper left corner
  uint32_t danger = 0;
  uint32_t height = height_map[0][0];
  if (height < height_map[1][0] && height < height_map[0][1]) {
    std::cout << "upper left corner " << height << std::endl;
    visit_low_point(0, 0);
  }

  //upper right corner
  height = height_map[0][col_count - 1];
  if ( height < height_map[0][col_count - 2] && height < height_map[1][col_count - 1]) {
     std::cout << "upper right corner " << height << std::endl;
    visit_low_point(0, col_count - 1);
  }

  // lower left corner
  height = height_map[row_count - 1][0];
  if (height < height_map[row_count - 2][0] && height < height_map[row_count - 1][1]) {
     std::cout << "lower left corner " << height << std::endl;
    visit_low_point(row_count - 1, 0);
  }

  // lower right corner
  height = height_map[row_count - 1][col_count - 1];
  if (height < height_map[row_count - 2][col_count -1] && height < height_map[row_count - 1][col_count - 2]) {
    std::cout << "lower right corner " << height << std::endl;
    visit_low_point(row_count - 1, col_count - 1);
  }

  //Upper row
  for (uint32_t col = 1; col < col_count - 1; ++col) {
    height = height_map[0][col];
    if (height < height_map[0][col - 1]
    &&  height < height_map[1][col]
    &&  height < height_map[0][col + 1]) {
      std::cout << "upper row col " << col << " " << height << std::endl;
      visit_low_point(0, col);
    }
  }

  //Lower row
  for (uint32_t col = 1; col < col_count - 1; ++col) {
    height = height_map[row_count - 1][col];
    if (height < height_map[row_count - 1][ col - 1]
    &&  height < height_map[row_count - 2][col]
    &&  height < height_map[row_count - 1][col + 1]) {
      std::cout << "lower row col " << col << " " << height << std::endl;
      visit_low_point(row_count - 1, col);
    }
  }

  //Left column
  for (uint32_t row = 1; row < row_count - 1; ++row) {
    height = height_map[row][0];
    if (height < height_map[row - 1][0]
    &&  height < height_map[row][1]
    &&  height < height_map[row + 1][0]) {
      std::cout << "left column row " << row << " " << height << std::endl;
      visit_low_point(row, 0);
    }
  }

  //Right column
  for (uint32_t row = 1; row < row_count - 1; ++row) {
    height = height_map[row][col_count - 1];
    if (height < height_map[row - 1][col_count - 1]
    &&  height < height_map[row][col_count - 2]
    &&  height < height_map[row + 1][col_count - 1]) {
      std::cout << "right column row " << row << " " << height << std::endl;
      visit_low_point(row, col_count - 1);
    }
  }

  // Center grid
  for (uint32_t row = 1; row < row_count - 1; ++row) {
    for (uint32_t col = 1; col < col_count - 1; ++col) {
      height = height_map[row][col];
      if (height < height_map[row - 1][col]
      &&  height < height_map[row + 1][col]
      &&  height < height_map[row][col - 1]
      &&  height < height_map[row][col + 1]) {
        visit_low_point(row, col);
      }
    }
  }
}

uint32_t RegionSearch(const uint32_t row_count, const uint32_t col_count, const uint32_t start_row, const uint32_t start_col,
                      const std::vector<std::vector<uint32_t>>& height_map) {
  std::set<std::pair<uint32_t, uint32_t>> visited;
  std::list<std::pair<uint32_t, uint32_t>> open;
  uint32_t terminate_count = 0;
  open.push_back(std::make_pair(start_row, start_col));
  while (!open.empty()) {
    const auto element = open.front();
    open.pop_front();
    if (visited.contains(element)) {
      continue;
    }
    visited.insert(element);
    if (height_map[element.first][element.second] == 9) {
      ++terminate_count;
      continue;
    }
    if (element.first == 0 && element.second == 0) {
      open.push_back(std::make_pair(1, 0));
      open.push_back(std::make_pair(0, 1));
    } else if (element.first == 0 && element.second == col_count - 1) {
      open.push_back(std::make_pair(1, col_count - 1));
      open.push_back(std::make_pair(0, col_count - 2));
    } else if (element.first == row_count -1 && element.second == 0) {
        open.push_back(std::make_pair(row_count - 2, 0));
        open.push_back(std::make_pair(row_count - 1, 1));
    } else if (element.first == row_count - 1 && element.second == col_count - 1) {
      open.push_back(std::make_pair(row_count - 2, col_count - 1));
      open.push_back(std::make_pair(row_count - 1, col_count - 2));
    } else if (element.first == 0) {
      open.push_back(std::make_pair(0, element.second - 1));
      open.push_back(std::make_pair(1, element.second));
      open.push_back(std::make_pair(0, element.second + 1));
    } else if (element.first == row_count -1 ) {
      open.push_back(std::make_pair(row_count - 1, element.second - 1));
      open.push_back(std::make_pair(row_count - 2 , element.second));
      open.push_back(std::make_pair(row_count - 1, element.second + 1));
    } else if (element.second == 0) {
      open.push_back(std::make_pair(element.first - 1, 0));
      open.push_back(std::make_pair(element.first , 1));
      open.push_back(std::make_pair(element.first + 1, 0));
    } else if (element.second == col_count - 1) {
      open.push_back(std::make_pair(element.first - 1, col_count - 1));
      open.push_back(std::make_pair(element.first , col_count - 2));
      open.push_back(std::make_pair(element.first + 1, col_count - 1));
    } else {
      open.push_back(std::make_pair(element.first - 1, element.second));
      open.push_back(std::make_pair(element.first + 1, element.second));
      open.push_back(std::make_pair(element.first, element.second - 1));
      open.push_back(std::make_pair(element.first, element.second + 1));
    }
  }
  return visited.size() - terminate_count;
}

int main(int argc, char** argv) {
  auto lines = ParseLinesFromFile(argv[1]);
  std::vector<uint32_t> init_row;
  init_row.resize(lines.begin()->size());

  std::vector<std::vector<uint32_t>> height_map_mut;
  height_map_mut.resize(lines.size(), init_row);

  uint32_t row_count = lines.size();
  uint32_t col_count = init_row.size();

  std::cout << "row count " << row_count << " col count " << col_count << std::endl;
  for (uint32_t row = 0;  row < row_count; ++row) {
    for (uint32_t col = 0; col < col_count; ++col) {
      height_map_mut[row][col] = static_cast<uint32_t>(lines[row][col]) - static_cast<uint32_t>('0');
    }
  }

  uint32_t danger = 0;
  FindLowPoints(row_count, col_count, height_map_mut, [&danger, &height_map_mut](auto row, auto col) {
    danger += height_map_mut[row][col] + 1;
  });

  std::cout << "danger " << danger << std::endl;

  std::vector<uint32_t> region_sizes;
  FindLowPoints(row_count, col_count, height_map_mut, [&](auto row, auto col) mutable {
    region_sizes.push_back(RegionSearch(row_count, col_count, row, col, height_map_mut));
  });

  std::sort(region_sizes.begin(), region_sizes.end(), [](auto a, auto b) { return a > b;});

  uint32_t region_danger = region_sizes[0] * region_sizes[1] * region_sizes[2];
  std::cout << "region danger " << region_danger << std::endl;
}

