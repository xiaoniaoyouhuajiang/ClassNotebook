cmake_minimum_required(VERSION 3.10)
project(lab2_OOP)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES *.h *.cpp Armor/*.h Armor/*.cpp Factory/*.h Factory/*.cpp FlyWeight/*.h FlyWeight/*.cpp
        Observers/*.h Observers/*.cpp Proxy/*.h Proxy/*.cpp Strategy/*.h Strategy/*.cpp
        Unit/Archer/*.h Unit/Archer/*.cpp Unit/Viking/*.h Unit/Viking/*.cpp
        Unit/Wizard/*.h Unit/Wizard/*.cpp Unit/*.h Unit/*.cpp Weapon/*.h Weapon/*.cpp
        Weapon/Far/*.h Weapon/Far/*.cpp Weapon/Magic/*.h Weapon/Magic/*.cpp
        Weapon/Physic/*.h Weapon/Physic/*.cpp)

add_executable(lab2_OOP ${SOURCE_FILES} ${SOURCES} Texture/Texture.h Texture/SwampTexture.h Texture/GrassTexture.h Texture/RockTexture.h NeutralObject/NeutralObject.h NeutralObject/MageGuild.h NeutralObject/HolyGrail.h NeutralObject/House.h NeutralObject/Battlefield.h NeutralObject/WildAnimalsArea.h FieldCell.cpp FieldCell.h FlyWeight/ArmorFlyWeight.cpp FlyWeight/WeaponFlyWeight.cpp GameUI/GameInfo.h GameUI/Requests/AttackRequest.h GameUI/Requests/AttackUnitRequest.h GameUI/Requests/Request.h GameUI/Requests/CreateBaseRequest.h GameUI/Requests/CreateRequest.h GameUI/Requests/CreateUnitRequest.h GameUI/Requests/MoveRequest.h GameUI/Requests/MoveUnitRequest.h GameUI/Requests/ShowBaseRequest.h GameUI/Requests/ShowRequest.h GameUI/Requests/ShowUnitRequest.h GameUI/GameAPI.h Logging/Formats/LogFormat.h Logging/Formats/NoFormat.h Logging/Formats/TagFormat.h Logging/Formats/TimeFormat.h Proxy/LogProxy.h Logging/Loggers/FileLogger.h Logging/Logend.h Logging/Loggers/Logger.h Logging/Loggers/NoLogger.h Logging/Loggers/TerminalLogger.h Logging/Log.cpp Logging/Log.h GameUI/Requests/ExitRequest.h GameUI/Memento/RequestMemento.h GameUI/Memento/LoadRequest.h GameUI/Memento/SaveRequest.h GameUI/LoadedRequestInterpreter.h GameUI/MainRequestInterpreter.h Utils.h GameUI/Rules/HugeGame.h GameUI/Rules/GamingRule.h GameUI/Rules/PlayerState.h GameUI/Rules/TinyGame.h GameUI/Requests/NewRequest.h GameUI/Requests/NewGameRequest.h Exceptions/DoublePlacingOnFieldException.h Exceptions/GameFieldOutOfRangeException.h Exceptions/ImpossibleMoveException.h Exceptions/InvalidFileLoaddingException.h Exceptions/DoubleBasePlacingException.h)