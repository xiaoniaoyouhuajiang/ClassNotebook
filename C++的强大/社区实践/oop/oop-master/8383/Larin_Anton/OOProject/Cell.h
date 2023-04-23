//
// Created by anton on 5/10/20.
//

#ifndef OOPROJECT_CELL_H
#define OOPROJECT_CELL_H

#include <memory>

#include "GameObject/GameObject.h"
#include "GameObject/Unit/Unit.h"
#include "GameObject/Terrain/TerrainProxy.h"
#include "GameObject/Entity/Entity.h"

class Cell {
public:
    Cell(std::shared_ptr<Unit> &unit);

    Cell();

    Cell(const Cell & src);

    std::shared_ptr<Unit> getUnit();

    void setUnit(std::shared_ptr<Unit> unit);

    std::shared_ptr<TerrainProxy> getTerrain();

    void setTerrain(std::shared_ptr<TerrainProxy> terrain);

    std::shared_ptr<Entity> getEntity();

    void setEntity(std::shared_ptr<Entity> entity);

private:
    std::shared_ptr<Unit> unit;
    std::shared_ptr<TerrainProxy> terrain;
    std::shared_ptr<Entity> entity;
};


#endif //OOPROJECT_CELL_H
