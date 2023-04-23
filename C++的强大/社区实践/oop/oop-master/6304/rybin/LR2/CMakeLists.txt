cmake_minimum_required (VERSION 3.8)

project(LAB2_OOP)

add_executable(manual_test manual_test.cpp)

add_library(Shape STATIC Shape_Point.cpp Circle.cpp Square.cpp Triangle.cpp)

target_link_libraries(manual_test Shape)

target_compile_features(manual_test PUBLIC cxx_std_11)