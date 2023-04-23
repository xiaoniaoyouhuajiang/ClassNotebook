cmake_minimum_required(VERSION 3.15)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1 main.cpp GameField.cpp GameField.h Unit.cpp Unit.h Alliance.cpp Alliance.h Peon.cpp Peon.h Shooter.cpp Shooter.h Orcs.cpp Orcs.h Troll.cpp Troll.h Goblin.cpp Goblin.h Magicians.cpp Magicians.h Elf.cpp Elf.h Witch.cpp Witch.h)