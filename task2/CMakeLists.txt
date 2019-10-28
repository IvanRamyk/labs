cmake_minimum_required(VERSION 3.14)
project(task2)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(task2 Sources/main.cpp Headers/Translate.h Headers/Translate.hxx Test/Test.h Headers/Function.h Test/TestFunction.cpp)
target_link_libraries(task2 gtest gtest_main)