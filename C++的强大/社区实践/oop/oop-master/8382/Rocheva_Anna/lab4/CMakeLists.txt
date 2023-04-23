cmake_minimum_required(VERSION 3.15)
project(labOOP)

set(CMAKE_CXX_STANDARD 17)

add_executable(labOOP main.cpp GameField.cpp GameField.hpp FieldCell.cpp FieldCell.hpp
        objects/Base.cpp objects/Base.hpp objects/units/Unit.cpp objects/units/Unit.hpp
        objects/neutralObjects/NeutralObject.cpp objects/neutralObjects/NeutralObject.hpp
        landscapes/Landscape.cpp landscapes/Landscape.hpp Manager.cpp Manager.hpp objects/Object.cpp
        objects/Object.hpp objects/units/attributes/Attribute.cpp objects/units/attributes/Attribute.hpp
        objects/units/attributes/Health.cpp objects/units/attributes/Health.hpp objects/units/people/People.cpp
        objects/units/people/People.hpp objects/units/people/Infantry.cpp objects/units/people/Infantry.hpp
        objects/units/CompositeUnit.cpp objects/units/CompositeUnit.hpp objects/units/attributes/Attack.cpp
        objects/units/attributes/Attack.hpp objects/units/attributes/Defense.cpp objects/units/attributes/Defense.hpp
        objects/units/FactoryMethod.cpp objects/units/FactoryMethod.hpp landscapes/Grass.cpp landscapes/Grass.hpp
        landscapes/Proxy.cpp landscapes/Proxy.hpp objects/units/people/Guardsmen.cpp objects/units/people/Guardsmen.hpp
        objects/units/aircrafts/Aircraft.cpp objects/units/aircrafts/Aircraft.hpp objects/units/aircrafts/Fighter.cpp
        objects/units/aircrafts/Fighter.hpp objects/units/aircrafts/Scout.cpp objects/units/aircrafts/Scout.hpp
        objects/units/groundForces/GroundForce.cpp objects/units/groundForces/GroundForce.hpp
        objects/units/groundForces/Tank.cpp objects/units/groundForces/Tank.hpp objects/units/groundForces/Cannon.cpp
        objects/units/groundForces/Cannon.hpp landscapes/Mountains.cpp landscapes/Mountains.hpp landscapes/Forest.cpp
        landscapes/Forest.hpp landscapes/Swamp.cpp landscapes/Swamp.hpp objects/neutralObjects/Hospital.cpp
        objects/neutralObjects/Hospital.hpp objects/neutralObjects/TrainingBase.cpp
        objects/neutralObjects/TrainingBase.hpp objects/neutralObjects/Shop.cpp objects/neutralObjects/Shop.hpp
        objects/neutralObjects/Bar.cpp objects/neutralObjects/Bar.hpp objects/Subject.cpp objects/Subject.hpp
        objects/Observer.cpp objects/Observer.hpp objects/neutralObjects/Strategy.cpp objects/neutralObjects/Strategy.hpp
        Facade.cpp Facade.hpp commands/Command.cpp commands/Command.hpp commands/CreateUnitCommand.cpp
        commands/CreateUnitCommand.hpp commands/DeleteUnitCommand.cpp commands/DeleteUnitCommand.hpp commands/MoveUnitCommand.cpp
        commands/MoveUnitCommand.hpp commands/AttackUnitCommand.cpp commands/AttackUnitCommand.hpp commands/UnitsAttributesCommand.cpp
        commands/UnitsAttributesCommand.hpp commands/ActionWithObjectCommand.cpp commands/ActionWithObjectCommand.hpp
        commands/StartGameCommand.cpp commands/StartGameCommand.hpp loggers/Logger.cpp loggers/Logger.hpp loggers/FileLogger.cpp
        loggers/FileLogger.hpp loggers/TerminalLogger.cpp loggers/TerminalLogger.hpp loggers/NoLogger.cpp loggers/NoLogger.hpp
        loggers/LogProxy.cpp loggers/LogProxy.hpp loggers/Adapter.cpp loggers/Adapter.hpp Gamer.cpp Gamer.hpp)
