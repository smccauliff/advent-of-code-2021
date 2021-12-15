cmake_minimum_required(VERSION 3.20)
project(advent_of_code_2021)
find_package(Boost)

set(CMAKE_CXX_STANDARD 23)

include_directories(src/include)

add_library(aoc-2021 STATIC src/include/aoc-2021.hpp src/lib/aoc-2021.cpp)

add_library(bingo STATIC src/include/bingo.hpp src/lib/bingo.cpp)

target_include_directories(bingo PUBLIC Boost::headers)

add_executable(dec3-2 src/bin/dec3-2.cpp)

target_link_libraries(dec3-2 PRIVATE aoc-2021)

add_executable(dec4 src/bin/dec4.cpp)

target_link_libraries(dec4 PRIVATE bingo aoc-2021)

