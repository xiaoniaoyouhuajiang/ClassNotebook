cmake_minimum_required(VERSION 3.15)
project(sem4_oop_game)

set(CMAKE_CXX_STANDARD 17)

link_libraries(raylib)

add_executable(sem4_oop_game main.cpp Units/BaseUnit.hpp Field/Field.cpp Field/Field.hpp TwoDimensionalArray.hpp Units/Unit.hpp Game.hpp Gui/Gui.cpp Gui/Gui.hpp Units/Knights/HeavyKnightUnit.hpp FieldPosition.hpp Units/Knights/KnightUnit.hpp Units/Knights/LightweightKnightUnit.hpp Units/Archers/ArcherUnit.hpp Units/Archers/PowerfulArcherUnit.hpp Units/Archers/DistanceArcherUnit.hpp Units/Mages/MageUnit.hpp Units/Mages/IceMageUnit.hpp Units/Mages/FireMageUnit.hpp Field/FieldIterator.cpp Field/FieldIterator.hpp Units/UnitFactory.hpp Units/ConcreteUnitFactory.hpp Gui/GuiConstants.hpp Gui/NewUnitSelectionScreen.cpp Gui/NewUnitSelectionScreen.hpp Gui/GuiTools.cpp Gui/GuiTools.hpp Gui/UnitInfoScreen.cpp Gui/UnitInfoScreen.hpp Terrains/Terrain.hpp Terrains/GroundTerrain.hpp Terrains/WaterTerrain.hpp Terrains/StoneTerrain.hpp Field/FieldCell.cpp Field/FieldCell.hpp Terrains/TerrainFactory.hpp Terrains/ConcreteTerrainFactory.hpp Units/BaseUnit.cpp Base.cpp Base.hpp WithHealth.hpp Creature.hpp Things/Thing.hpp Things/MedicineThing.hpp Things/PowerfulMedicineThing.hpp Things/Thing.cpp GameInterface.hpp Logging/GameProxyWithConsoleLogging.hpp Logging/Logger.hpp Logging/GameProxyWithLogging.hpp Logging/PlainLoggerToOstreamAdapter.hpp Logging/WithTimeLoggerToOstreamAdapter.hpp Logging/GameProxyWithFileLogging.hpp Gui/TextButton.hpp Gui/TextButton.cpp PlayerState.cpp PlayerState.hpp GameEndRule.hpp GameStartRule.hpp GameMemento.hpp GameMemento.cpp)
