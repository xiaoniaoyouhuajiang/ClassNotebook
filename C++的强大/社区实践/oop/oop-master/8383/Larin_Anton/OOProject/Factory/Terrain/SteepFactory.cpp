//
// Created by anton on 5/26/20.
//

#include "SteepFactory.h"

#include "../../GameObject/Terrain/SteepTerrain.h"

SteepFactory::SteepFactory(int steepness, int enhancedSteepness) : AbstractTerrainFactory(steepness),
                                                                   enhancedSteepness(enhancedSteepness) {}

std::shared_ptr<GameObject> SteepFactory::createObject(int x, int y, Devotion devotion) {
    auto rPtr = std::make_shared<SteepTerrain>(x,y,enhancedSteepness);
    return std::static_pointer_cast<GameObject>(rPtr);
}
