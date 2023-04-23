cmake_minimum_required(VERSION 3.13)
project(OOP)

set(CMAKE_CXX_STANDARD 14)

add_executable(OOP main.cpp
        Unit
        Infantry
        Cavalry
        Archer
        Field
        Object
        Landscape
        Mountain
        Water
        Forest
        Plain
        Base
        NeutralObject
        Hospital
        PublicHouse
        WorkShop
        Bar
        Game
        Interaction
        UnitAction
        BaseAction
        Log
        Proxy
        )