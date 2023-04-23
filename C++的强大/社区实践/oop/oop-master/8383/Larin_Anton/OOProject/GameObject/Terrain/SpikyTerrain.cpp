//
// Created by anton on 5/16/20.
//

#include "SpikyTerrain.h"



void SpikyTerrain::restep(std::shared_ptr<GameObject> sbj) {
    sbj->getVitality().damage(damage);
}

SpikyTerrain::SpikyTerrain(int x, int y, int steepness, int damage)
        : Terrain(x, y, CommonClass::SpikyTerrain, TerrainType::SpikyTerrain, steepness), damage(damage) {}


CommonClass SpikyTerrain::getObjectClass() {
    return CommonClass ::SpikyTerrain;
}
