//
// Created by anton on 5/26/20.
//

#include "SpikyFactory.h"

#include "../../GameObject/Terrain/SpikyTerrain.h"

SpikyFactory::SpikyFactory(int steepness, int damage) : AbstractTerrainFactory(steepness), damage(damage) {}

std::shared_ptr<GameObject> SpikyFactory::createObject(int x, int y, Devotion devotion) {
    auto rPtr = std::make_shared<SpikyTerrain>(x,y,steepness,damage);
    return std::static_pointer_cast<GameObject>(rPtr);
}
