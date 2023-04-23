cmake_minimum_required(VERSION 2.8)
project(OOP_L6)
set(CMAKE_CXX_FLAGS "-std=c++11 -ggdb")

find_package(GTest REQUIRED)
include_directories(include ${GTEST_INCLUDE_DIRS})

set (FIGURES src/point.cpp src/shape.cpp src/color.cpp include/shape.hpp include/circle.hpp include/regular_pentagon.hpp)
set (AUX include/vector.hpp include/shared_ptr.hpp include/alg.hpp)
set (SOURCE src/main.cpp)
set (TESTSOURCE src/tests.cpp)

add_executable(lab6 ${FIGURES} ${SOURCE} ${AUX})
add_executable(lab6test ${FIGURES} ${TESTSOURCE})
target_link_libraries(lab6test ${GTEST_LIBRARIES} pthread)
enable_testing()
add_test(lab6test "./lab6test")