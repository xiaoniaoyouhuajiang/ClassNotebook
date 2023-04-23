#pragma once

#include "Terrain.hpp"
#include "ConcreteTerrainFactory.hpp"

class StoneTerrain : public Terrain {
public:
    std::shared_ptr<TerrainFactory> createTerrainFactory() const override {
        return std::make_shared<ConcreteTerrainFactory<StoneTerrain>>();
    }
    std::shared_ptr<Terrain> createCopy() const override {
        return std::make_shared<StoneTerrain>();
    }

    bool canHoldSomething() const override {
        return false;
    }
    bool unitCanAttackHere() const override {
        return false;
    }
};