#pragma once

#include "Terrain.hpp"
#include "ConcreteTerrainFactory.hpp"

class GroundTerrain : public Terrain {
public:
    std::shared_ptr<TerrainFactory> createTerrainFactory() const override {
        return std::make_shared<ConcreteTerrainFactory<GroundTerrain>>();
    }
    std::shared_ptr<Terrain> createCopy() const override {
        return std::make_shared<GroundTerrain>();
    }

    bool canHoldSomething() const override {
        return true;
    }
    bool unitCanAttackHere() const override {
        return true;
    }
};