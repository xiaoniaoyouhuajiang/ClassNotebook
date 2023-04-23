cmake_minimum_required(VERSION 3.1.0)

#configure_file(CMakeLists.txt.in
#               googletest-download/CMakeLists.txt)
#execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
#execute_process(COMMAND ${CMAKE_COMMAND} --build .
#  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
 
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
 
#add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
#                 ${CMAKE_BINARY_DIR}/googletest-build)
 

set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_definitions(-D_USE_MATH_DEFINES)
set (CMAKE_CXX_STANDARD 11)
add_executable(oop2 main.cc)
# target_link_libraries(oop2 gtest)
