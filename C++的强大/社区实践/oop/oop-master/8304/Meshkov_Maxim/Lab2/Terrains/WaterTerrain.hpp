#pragma once

#include "Terrain.hpp"
#include "ConcreteTerrainFactory.hpp"

class WaterTerrain : public Terrain {
public:
    std::shared_ptr<TerrainFactory> createTerrainFactory() const override {
        return std::make_shared<ConcreteTerrainFactory<WaterTerrain>>();
    }
    std::shared_ptr<Terrain> createCopy() const override {
        return std::make_shared<WaterTerrain>();
    }

    bool canHoldSomething() const override {
        return true;
    }
    bool unitCanAttackHere() const override {
        return false;
    }
};