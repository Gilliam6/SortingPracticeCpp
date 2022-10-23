cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
find_package(Matplot++ REQUIRED)

project(Sorting)
add_executable(Sorting selectionSort.cpp)
target_link_libraries(Sorting PUBLIC Matplot++::matplot)

