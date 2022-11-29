cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER "g++")
find_package(Matplot++ REQUIRED)

project(Sorting)
add_executable(Sorting main.cpp Sort.cpp Benchmark.cpp)
target_link_libraries(Sorting PUBLIC Matplot++::matplot)

