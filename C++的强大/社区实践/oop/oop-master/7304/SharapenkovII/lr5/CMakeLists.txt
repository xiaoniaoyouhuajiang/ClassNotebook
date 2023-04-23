cmake_minimum_required(VERSION 3.13)
project(Xgame)

set(CMAKE_CXX_STANDARD 17)

include_directories(../ultralight/include)

add_executable(Xgame main.cpp field/Field.cpp field/Field.h field/Cell.cpp field/Cell.h unit/Unit.cpp unit/Unit.h impediment/Impediment.cpp impediment/Impediment.h gui/UI.cpp gui/UI.h runtime/Game.cpp runtime/Game.h player/Player.cpp player/Player.h gui/GUI.cpp gui/GUI.h impediment/StaticImpediment.cpp impediment/StaticImpediment.h impediment/DynamicImpediment.cpp impediment/DynamicImpediment.h utility/Coord.cpp utility/Coord.h impediment/ImpedimentOrchestrator.cpp impediment/ImpedimentOrchestrator.h logger/Logger.cpp logger/Logger.h exception/Exception.h unit/OwnUnits.cpp unit/OwnUnits.h)

target_link_libraries(Xgame -lUltralight -lUltralightCore -lWebCore -lAppCore)