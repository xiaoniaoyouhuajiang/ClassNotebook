//
// Created by anton on 5/31/20.
//

#include "FlyCell.h"

GameObjectFlyWeight *FlyCell::getUnit() const {
    return &(*unit);
}

GameObjectFlyWeight *FlyCell::getTerrain() const {
    return &(*terrain);
}

GameObjectFlyWeight *FlyCell::getEntity() const {
    return &(*entity);
}

void FlyCell::setUnit(GameObjectFlyWeight *unit) {
    std::shared_ptr<GameObjectFlyWeight> ptr;
    if(unit) {
        ptr = std::make_shared<GameObjectFlyWeight>();
        *ptr = *unit;
    }else{
        ptr=std::shared_ptr<GameObjectFlyWeight>(nullptr);
    }
    FlyCell::unit = ptr;
}

void FlyCell::setTerrain(GameObjectFlyWeight *terrain) {
    std::shared_ptr<GameObjectFlyWeight> ptr;
    if(terrain) {
        ptr = std::make_shared<GameObjectFlyWeight>();
        *ptr = *terrain;
    }else{
        ptr=std::shared_ptr<GameObjectFlyWeight>(nullptr);
    }
    FlyCell::terrain = ptr;
}

void FlyCell::setEntity(GameObjectFlyWeight *entity) {
    std::shared_ptr<GameObjectFlyWeight> ptr;
    if(entity) {
        ptr = std::make_shared<GameObjectFlyWeight>();
        *ptr = *entity;
    }else{
        ptr=std::shared_ptr<GameObjectFlyWeight>(nullptr);
    }
    FlyCell::entity = ptr;
}
