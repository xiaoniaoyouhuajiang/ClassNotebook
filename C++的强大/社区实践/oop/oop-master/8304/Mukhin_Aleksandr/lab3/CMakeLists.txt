cmake_minimum_required(VERSION 3.15)
project(lab2)

set(CMAKE_CXX_STANDARD 20)
include_directories(
        mediators
        parameters
        ./
        units/civilians
        units/military
        units/government
        units
        landscapes
        creators
        creators/        creators/civiliansCreator
        creators/militaryCreator
        creators/governmentCreator
        neutralObject
        tests
        commands
)
add_executable(lab2
        tests/test.cpp
        tests/catch.hpp
        creators/Creator.h
        creators/Creator.cpp
#                main.cpp
        Base.cpp
        Base.h
        Boardfield.cpp
        Boardfield.h
        units/military/SpecialForces.cpp
        units/military/SpecialForces.h
        Cell.cpp
        Cell.h
        landscapes/Fire.cpp
        landscapes/Fire.h
        parameters/HealthPoints.cpp
        parameters/HealthPoints.h
        parameters/Attack.cpp
        parameters/Attack.h
        units/Unit.cpp
        units/Unit.h
        landscapes/Landscape.cpp
        landscapes/Landscape.h
        units/military/Military.cpp
        units/military/Military.h
        creators/militaryCreator/MilitaryCreator.cpp
        creators/militaryCreator/MilitaryCreator.h
        creators/militaryCreator/SpecialForcesCreator.cpp
        creators/militaryCreator/SpecialForcesCreator.h
        units/civilians/Civilians.cpp
        units/civilians/Civilians.h
        units/civilians/Doctor.cpp
        units/civilians/Doctor.h
        creators/civiliansCreator/CiviliansCreator.cpp
        creators/civiliansCreator/CiviliansCreator.h
        creators/civiliansCreator/DoctorCreator.cpp
        creators/civiliansCreator/DoctorCreator.h
        units/military/Airborne.cpp units/military/Airborne.h
        creators/militaryCreator/AirborneCreator.cpp
        creators/militaryCreator/AirborneCreator.h
        units/civilians/Engineer.cpp units/civilians/Engineer.h
        creators/civiliansCreator/EngineerCreator.cpp
        creators/civiliansCreator/EngineerCreator.h
        units/government/Government.cpp units/government/Government.h
        units/government/Ambassador.cpp units/government/Ambassador.h
        creators/governmentCreator/GovernmentCreator.cpp
        creators/governmentCreator/GovernmentCreator.h
        creators/governmentCreator/AmbassadorCreator.cpp
        creators/governmentCreator/AmbassadorCreator.h
        units/government/Ministry.cpp units/government/Ministry.h
        creators/governmentCreator/MinistryCreator.cpp
        creators/governmentCreator/MinistryCreator.h
        landscapes/Mountains.cpp
        landscapes/Mountains.h
        landscapes/Champaign.cpp
        landscapes/Champaign.h
        neutralObject/NeutralObject.cpp
        neutralObject/NeutralObject.h
        neutralObject/FireExtinguisher.cpp
        neutralObject/FireExtinguisher.h
        neutralObject/Sword.cpp
        neutralObject/Sword.h
        neutralObject/Serum.cpp
        neutralObject/Serum.h
        neutralObject/SuperNeutralObject.cpp
        neutralObject/SuperNeutralObject.h
        tests/catch.hpp
        BaseComponent.cpp BaseComponent.h mediators/BaseMediator.h mediators/Mediator.cpp mediators/Mediator.h commands/Command.cpp commands/Command.h commands/UnaryInteractionCommand.cpp commands/UnaryInteractionCommand.h commands/Invoker.cpp commands/Invoker.h commands/BinaryInteractionCommand.cpp commands/BinaryInteractionCommand.h Facade.cpp Facade.h)