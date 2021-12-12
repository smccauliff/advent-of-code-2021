#include <aoc-2021.hpp>

#include <algorithm>
#include <iostream>


using namespace aoc2021;

int main(int argc, char** argv) {

  auto lines = ParseLinesFromFile(argv[1]);

  LifeSupportComputer lsc(lines);
  // too low 1003024
  std::cout << lsc.LifeSupportReadings() << std::endl;

}