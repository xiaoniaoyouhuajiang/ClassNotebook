#pragma once

#include "TerrainFactory.hpp"

template <typename T>
class ConcreteTerrainFactory : public TerrainFactory {
public:
    std::shared_ptr<Terrain> create() const override {
        return std::make_shared<T>();
    };
};