#pragma once

#include <raylib.h>
#include <memory>

#include "TerrainFactory.hpp"

class Terrain {
public:
    virtual std::shared_ptr<TerrainFactory> createTerrainFactory() const = 0;
    virtual std::shared_ptr<Terrain> createCopy() const = 0;

    virtual bool canHoldSomething() const = 0;
    virtual bool unitCanAttackHere() const = 0;
};