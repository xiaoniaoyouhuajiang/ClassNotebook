project(headers)

add_library(
        headers
        STATIC
        Boardfield.h
        Unit.h
        ../Boardfield.cpp
        Array.hpp
        Infantry.h
        ../Infantry.cpp
        ../InfantryCreator.cpp
        InfantryCreator.h
        ../Creator.cpp
        Creator.h
        ../Archers.cpp Archers.h
        ../Cavalry.cpp Cavalry.h
        ../ArchersCreator.cpp
        ArchersCreator.h
        ../CavalryCreator.cpp
        CavalryCreator.h
        ../ArchersJunior.cpp
        ArchersJunior.h
        ../ArchersJuniorCreator.cpp
        ArchersJuniorCreator.h
        ../ArchersSenior.cpp
        ArchersSenior.h
        ../ArchersSeniorCreator.cpp
        ArchersSeniorCreator.h
        ../CavalryJunior.cpp
        CavalryJunior.h
        ../CavalryJuniorCreator.cpp
        CavalryJuniorCreator.h
        ../CavalrySenior.cpp
        CavalrySenior.h
        ../CavalrySeniorCreator.cpp
        CavalrySeniorCreator.h
        ../InfantryJunior.cpp
        InfantryJunior.h
        ../InfantryJuniorCreator.cpp
        InfantryJuniorCreator.h ../InfantrySenior.cpp InfantrySenior.h ../InfantrySeniorCreator.cpp InfantrySeniorCreator.h Iterator.hpp)