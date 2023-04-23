//
// Created by anton on 5/26/20.
//

#include "HollyFactory.h"

#include "../../GameObject/Terrain/HollyTerrain.h"

HollyFactory::HollyFactory(int steepness, int healAmount) : AbstractTerrainFactory(steepness), healAmount(healAmount) {}

std::shared_ptr<GameObject> HollyFactory::createObject(int x, int y, Devotion devotion) {

    auto rPtr = std::make_shared<HollyTerrain>(x,y,healAmount);
    return std::static_pointer_cast<GameObject>(rPtr);
}
