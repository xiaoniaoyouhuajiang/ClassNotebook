cmake_minimum_required (VERSION 3.8)

project(LAB5_OOP)

add_executable (poly_logic main.cpp)

add_library(MyAlgorithm MyAlgorithm.cpp)
add_library(Shape Shape_Point.cpp Square.cpp Triangle.cpp Circle.cpp)

target_link_libraries(poly_logic MyAlgorithm Shape)

target_compile_features(poly_logic PUBLIC cxx_std_11)