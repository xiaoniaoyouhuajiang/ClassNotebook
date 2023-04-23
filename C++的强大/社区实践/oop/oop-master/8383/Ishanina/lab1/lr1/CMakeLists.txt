cmake_minimum_required(VERSION 3.15)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp Units/Unit.cpp Units/Unit.h Units/ObjectInterface.h Units/Infantryman/Infantryman.h Units/Cavalryman/Cavalryman.h Units/Artillerist/Artillerist.h Units/Artillerist/Magician.cpp Units/Artillerist/Magician.h Units/Artillerist/Archer.cpp Units/Artillerist/Archer.h Units/Cavalryman/ElfOnUnicorn.cpp Units/Cavalryman/ElfOnUnicorn.h Units/Cavalryman/KnightOnHorse.cpp Units/Cavalryman/KnightOnHorse.h Units/Infantryman/Gnome.cpp Units/Infantryman/Gnome.h Units/Infantryman/Knight.cpp Units/Infantryman/Knight.h Field/Field.cpp Field/Field.h AbstractFactory/AbstractFactory.h AbstractFactory/ConcreteFactoryStrongHero.h AbstractFactory/ConcreteFactoryMagicHero.h)