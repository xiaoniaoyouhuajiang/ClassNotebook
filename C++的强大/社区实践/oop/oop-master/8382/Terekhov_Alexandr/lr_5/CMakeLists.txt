cmake_minimum_required(VERSION 3.10)
project(OOP)

set(CMAKE_CXX_STANDARD 17)

add_executable(OOP Logger.cpp AbstractObject.h main.cpp Unit.cpp World.cpp Game.cpp NeutralObject.cpp)
