cmake_minimum_required(VERSION 3.15)
project(oop1)

set(CMAKE_CXX_STANDARD 14)

add_executable(oop1 main.cpp Unit.h Field.h Condition.h Soldier.h YoungSoldier.h OldSildier.h Shooter.h KeenShooter.h SlantingShooter.h Tankman.h LightTankman.h HeavyTankman.h Field.cpp HeavyTankman.cpp KeenShooter.cpp LightTankman.cpp OldSoldier.cpp Shooter.cpp SlantingShooter.cpp Soldier.cpp Tankman.cpp Unit.cpp YoungSoldier.cpp Iterator.cpp Iterator.h FactoryUnit.h FactorySoldier.h FactoryShooter.h FactoryTankman.h Landscape.h Wall.h Water.h Ground.h LandscapeProtected.h Base.cpp Base.h SubjectObserve.h Observer.h SubjectObserve.cpp CompositUnit.cpp CompositUnit.h NeutralObject.h Poisen.h Potion.h DrinkStrong.h DrinkStamina.h Handler.h Command.h Mediator.h Mediator.cpp UnitMediator.h Facade.h Facade.cpp Logger.h Adapter.h LoggerProtected.h File.h Adapter.cpp SnapshotField.cpp SnapshotField.h Cell.h Game.h Rules.h State.h)