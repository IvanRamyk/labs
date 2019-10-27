cmake_minimum_required(VERSION 3.14)
project(task1)

set(CMAKE_CXX_STANDARD 14)

add_executable(task1 Sources/main.cpp Sources/Cargo.cpp Headers/Cargo.h Headers/Transport.h Sources/Transport.cpp Headers/Stock.h Sources/Stock.cpp)