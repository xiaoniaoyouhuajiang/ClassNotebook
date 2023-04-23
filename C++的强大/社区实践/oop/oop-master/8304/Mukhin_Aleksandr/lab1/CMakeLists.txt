cmake_minimum_required(VERSION 3.15.3)

project(lab1)
set(CMAKE_CXX_STANDARD 20)

add_executable(lab1 main.cpp Boardfield.cpp headers/Array.hpp)

include_directories(headers)
add_subdirectory(headers)
add_subdirectory(Google_tests)

target_link_libraries(lab1 headers)
