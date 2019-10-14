cmake_minimum_required(VERSION 3.14)
project(game)

set(CMAKE_CXX_STANDARD 14)

add_executable(game main.cpp dice.h dice.cpp graph.h graph.hxx)