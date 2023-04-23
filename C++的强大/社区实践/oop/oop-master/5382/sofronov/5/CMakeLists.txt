cmake_minimum_required(VERSION 3.7)
project(5)

set(CMAKE_CXX_STANDARD 11)

find_package(GTest REQUIRED)
enable_testing()

include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES shared_ptr.h Shapes.cpp Shapes.h List.h generation.cpp test.cpp)
add_executable(5 ${SOURCE_FILES})

target_link_libraries(5 ${GTEST_BOTH_LIBRARIES})