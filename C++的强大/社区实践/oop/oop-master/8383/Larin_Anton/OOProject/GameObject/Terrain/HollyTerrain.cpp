//
// Created by anton on 5/16/20.
//

#include "HollyTerrain.h"

HollyTerrain::HollyTerrain(int x, int y, int amount)
        : Terrain(x, y, CommonClass::HollyTerrain, TerrainType::HollyTerrain, defaultSteepness), amount(amount) {}

void HollyTerrain::restep(std::shared_ptr<GameObject> sbj) {
    sbj->getVitality().heal(amount);
}

CommonClass HollyTerrain::getObjectClass() {
    return CommonClass::HollyTerrain;
}
