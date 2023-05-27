cmake_minimum_required(VERSION 3.16)
project(bpt_test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS " -Ofast")

add_executable(code bptree.hpp main.cpp vector.hpp exceptions.hpp)