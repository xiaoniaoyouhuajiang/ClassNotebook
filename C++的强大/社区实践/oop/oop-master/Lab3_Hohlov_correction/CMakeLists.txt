cmake_minimum_required(VERSION 3.15)
project(untitled13)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled13 main.cpp GameField/GameField.cpp GameField/GameField.h
        Objects/Units/Unit.cpp Objects/Units/Unit.h
        Weapon/Weapon.h
        Armor/Armor.h Point.cpp
        Point.h
        GameField/GameFieldIterator.h
        Objects/Units/Infantry/Infantry.h
        Weapon/Sword.h
        Weapon/Fireball.h
        Weapon/Bow.h
        Armor/Tunic.h
        Armor/ChainArmor.h
        Armor/LeatherArmor.h
        Armor/IronArmor.h
        Objects/Units/Wizard/Wizard.h
        Objects/Units/Archer/Archer.h
        Weapon/Storm.h
        Objects/Units/Infantry/SwordMan.h
        Objects/Units/Archer/CrossBowMan.h
        Objects/Units/Archer/BlockBowMan.h
        Objects/Units/Infantry/Berserk.h
        Weapon/Axe.h
        Objects/Units/Wizard/StormMage.h
        Objects/Units/Wizard/FireMage.h
        GameField/FieldCell.cpp
        GameField/FieldCell.h
        Landscapes/Landscape.h
        Objects/Base.cpp
        Objects/Base.h
        Objects/Neutrals/NeutralObject.h
        Objects/GameObject.cpp
        Objects/GameObject.h
        Observers/UnitObserver.h
        Landscapes/Field.h
        Landscapes/Desert.h
        Landscapes/Ocean.h
        Objects/Neutrals/House.h
        Objects/Neutrals/Hospital.h
        Objects/Neutrals/Garden.h
        Landscapes/LandscapeProxy.cpp
        Landscapes/LandscapeProxy.h
        Objects/Neutrals/School.h
        Objects/Neutrals/NeutralObjectStrategy/NeutralObjectStrategy.h
        Objects/Neutrals/NeutralObjectStrategy/NeutralObjectStrategy.h
        Objects/Neutrals/NeutralObjectStrategy/ArcherStrategy.h
        Objects/Neutrals/NeutralObjectStrategy/InfantryStrategy.h
        Objects/Neutrals/NeutralObjectStrategy/WizardStrategy.h
        Armor/ArmorFlyWeight.h Weapon/WeaponFlyWeight.h
        Armor/ArmorFlyWeight.cpp
        Weapon/WeaponFlyWeight.cpp
        Observers/BaseObserver.h UI/Commands/Command.h UI/Commands/Create/CreateBaseCommand.h UI/Commands/Create/CreateUnitCommand.h UI/Commands/Move/MoveUnitCommand.h UI/Commands/Show/ShowBaseCommand.h UI/Commands/Show/ShowUnitCommand.h UI/Commands/Show/ShowCommand.h UI/Commands/MainCommand.h UI/Commands/Create/CreateCommand.h UI/Commands/Move/MoveCommand.h GameFacade.h GameInfo.h UI/Commands/Attack/AttackCommand.h UI/Commands/Attack/AttackUnitCommand.h)