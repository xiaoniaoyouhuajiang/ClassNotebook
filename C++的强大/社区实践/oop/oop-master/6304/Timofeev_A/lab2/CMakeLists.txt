cmake_minimum_required (VERSION 3.10)

project(lab2)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11")

add_library(shape figures.cpp)
add_library(basis basis.cpp)

add_executable (lab2 lab2.cpp)

target_link_libraries(lab2 shape basis)

target_compile_features(lab2 PUBLIC cxx_std_11)