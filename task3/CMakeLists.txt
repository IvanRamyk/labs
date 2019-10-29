cmake_minimum_required(VERSION 3.14)
project(task3)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(task3 main.cpp Sources/Base1.cpp Headers/Base1.h Sources/Base2.cpp Headers/Base2.h Sources/Alpha.cpp Headers/Alpha.h Headers/Global.h Test/Test.cpp Test/Test.h Sources/Beta.cpp Headers/Beta.h Sources/Gamma.cpp Headers/Gamma.h Sources/Delta.cpp Headers/Delta.h)
target_link_libraries(task3 gtest gtest_main)