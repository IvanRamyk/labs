cmake_minimum_required(VERSION 3.14)
project(lab1)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(lab1 main.cpp dice.cpp dice.h graph.h graph.hxx tests/test_dice.cpp tests/test_graph.cpp)
target_link_libraries(lab1 gtest gtest_main)