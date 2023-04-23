#pragma once

#include <memory>
class Terrain;

class TerrainFactory {
public:
    virtual std::shared_ptr<Terrain> create() const = 0;
};