cmake_minimum_required(VERSION 3.10)

project(aoc VERSION 1.0)

add_executable(a program.cxx)

# Set C++11 standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

add_definitions(-std=c++11)

