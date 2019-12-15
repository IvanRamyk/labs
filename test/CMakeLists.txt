cmake_minimum_required(VERSION 3.15)
project(test)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(test main.cpp ../date.cpp ../source.cpp ../blogsystem.cpp ../blog.cpp ../topic.cpp testDate.cpp testSystem.cpp)
target_link_libraries(test gtest gtest_main)