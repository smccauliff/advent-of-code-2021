cmake_minimum_required(VERSION 3.20)
project(advent_of_code_2021)

set(CMAKE_CXX_STANDARD 23)

include_directories(src/include)

add_library(aoc-2021 STATIC src/include/aoc-2021.hpp src/lib/aoc-2021.cpp)

add_executable(dec3-2 src/bin/dec3-2.cpp)

target_link_libraries(dec3-2 PRIVATE aoc-2021)



