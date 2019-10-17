cmake_minimum_required(VERSION 3.14)
project(lab1)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(lab1 main.cpp src/dice.cpp src/dice.h src/graph.h src/graph.hxx tests/test_dice.cpp tests/test_graph.cpp tests/test.h)
target_link_libraries(lab1 gtest gtest_main)