//
// Created by anton on 5/9/20.
//

#ifndef OOPROJECT_STATS_H
#define OOPROJECT_STATS_H

#include <string>
#include <cassert>

static const int defaultSteepness = 2;
static const int highSteepness = 7;
static const int defaultRange= 2;
static const int highRange= 5;


enum class Devotion{
    Neuter,
    Light,
    Dark
};

enum class ObjectType{
    Unit,
    Entity,
    Terrain,
    NONE
};

enum class UnitType{
    AbleUnit,
    MobileUnit,
    EnduringUnit
};

enum class EntityType{
    HealEntity,
    TrapEntity,
    BlockEntity,
    PitEntity,
    Base
};



enum class CommonClass{
    NONE,
    TheRanger,
    ThePowerful,
    TheAgile,
    TheMarathoner,
    TheTough,
    TheVampire,
    SpikyTerrain,
    SteepTerrain,
    HollyTerrain,
    HealEntity,
    TrapEntity,
    BlockEntity,
    PitEntity,
    Base

};

static ObjectType classToType(CommonClass commonClass){
    switch (commonClass){

        case CommonClass::NONE:return ObjectType ::NONE;
        case CommonClass::TheRanger:return ObjectType ::Unit;
        case CommonClass::ThePowerful:return ObjectType ::Unit;
        case CommonClass::TheAgile:return ObjectType ::Unit;
        case CommonClass::TheMarathoner:return ObjectType ::Unit;
        case CommonClass::TheTough:return ObjectType ::Unit;
        case CommonClass::TheVampire:return ObjectType ::Unit;
        case CommonClass::SpikyTerrain:return ObjectType ::Terrain;
        case CommonClass::SteepTerrain:return ObjectType ::Terrain;
        case CommonClass::HollyTerrain:return ObjectType ::Terrain;
        case CommonClass::HealEntity:return ObjectType ::Entity;
        case CommonClass::TrapEntity:return ObjectType ::Entity;
        case CommonClass::BlockEntity:return ObjectType ::Entity;
        case CommonClass::PitEntity:return ObjectType ::Entity;
        case CommonClass::Base:return ObjectType ::Entity;
    }
}


enum class TerrainType{
    SpikyTerrain,
    SteepTerrain,
    HollyTerrain,
};

static TerrainType classToTerrain(CommonClass commonClass){
    assert(classToType(commonClass)==ObjectType::Terrain);
    switch(commonClass){
        case CommonClass::SpikyTerrain:return TerrainType::SpikyTerrain;
        case CommonClass::SteepTerrain:return TerrainType::SteepTerrain;
        case CommonClass::HollyTerrain:return TerrainType::HollyTerrain;
    }
};


enum class UnitClass{
    TheRanger,
    ThePowerful,
    TheAgile,
    TheMarathoner,
    TheTough,
    TheVampire
};

static CommonClass unitToCommon(UnitClass unitClass){
    switch (unitClass){
        case UnitClass::TheRanger:return CommonClass ::TheRanger;
        case UnitClass::ThePowerful:return CommonClass ::ThePowerful;
        case UnitClass::TheAgile:return CommonClass ::TheAgile;
        case UnitClass::TheMarathoner:return CommonClass ::TheMarathoner;
        case UnitClass::TheTough:return CommonClass ::TheTough;
        case UnitClass::TheVampire:return CommonClass ::TheVampire;
    }
}

static UnitClass commonToUnit(CommonClass commonClass){
    assert(classToType(commonClass)==ObjectType::Unit);
    switch (commonClass){
        case CommonClass ::TheRanger:
            return UnitClass::TheRanger;
        case CommonClass ::ThePowerful:
            return  UnitClass::ThePowerful;
        case CommonClass ::TheAgile:
            return UnitClass::TheAgile;
        case CommonClass ::TheMarathoner:
            return UnitClass::TheMarathoner;
        case CommonClass ::TheTough:
            return UnitClass::TheTough;
        case CommonClass ::TheVampire:
            return UnitClass::TheVampire;
    }
}

struct GameObjectFlyWeight{
    std::string name = "NoName";
    CommonClass commonClass = CommonClass::NONE;
    char symbol = ' ';
    Devotion devotion;

    bool hasStats = false;
    int health = -1;
    int cur=-1;
    int lim=-1;
};



#endif //OOPROJECT_STATS_H
