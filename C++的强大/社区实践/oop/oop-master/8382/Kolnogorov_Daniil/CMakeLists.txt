cmake_minimum_required(VERSION 3.1)

project(OOP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic")

find_library(RAYLIB_LIBRARY raylib)

include_directories(src/)

add_executable(run
	src/main.cpp
	src/Game/game.cpp
	src/Game/Rules/game_rule.cpp
	src/Game/Player/player.cpp
	src/Game/Field/field.cpp
	src/Game/Field/field_iterator.cpp
	src/Game/Field/field_proxy.cpp
	src/Game/Tiles/tiles.cpp
	src/Game/Tiles/base.cpp
	src/Game/Units/units.cpp
	src/Game/Neutral/powerup.cpp
	src/Game/Commands/interpreter.cpp
	src/UI/render.cpp
	src/UI/positioner.cpp
)

target_link_libraries(run ${RAYLIB_LIBRARY})
