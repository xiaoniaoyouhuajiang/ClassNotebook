cmake_minimum_required(VERSION 3.7)
project(2supernew)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest REQUIRED)
enable_testing()

include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES test.cpp Shapes.cpp)

add_executable(2supernew ${SOURCE_FILES})

target_link_libraries(2supernew ${GTEST_BOTH_LIBRARIES})