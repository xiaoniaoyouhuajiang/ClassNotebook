cmake_minimum_required(VERSION 3.6)
project(5)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
find_package(GTest REQUIRED)
add_subdirectory(figures)
add_subdirectory(list)
add_subdirectory(pointer)
enable_testing()

set(FIGURES_FILES figures/Shape.h figures/Shape.cpp figures/Circle.h figures/Circle.cpp
        figures/Pentangle.h figures/Pentangle.cpp figures/RegularPentangle.h figures/RegularPentangle.cpp)
set(LIST_FILES list/list.h)
set(POINTER_FILES pointer/shared_ptr.h)
set(SOURCE_FILES main.cpp extra/Solver.cpp extra/Solver.h)

add_executable(5 ${SOURCE_FILES} ${FIGURES_FILES} ${LIST_FILES} ${POINTER_FILES})

include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(5 ${GTEST_BOTH_LIBRARIES})