//
// Created by anton on 5/10/20.
//

#include "Cell.h"

Cell::Cell(std::shared_ptr<Unit> &unit) : unit(unit) {}

Cell::Cell() {
    unit = std::shared_ptr<Unit>(nullptr);
    terrain= std::shared_ptr<TerrainProxy>(nullptr);
    entity= std::shared_ptr<Entity>(nullptr);
}

std::shared_ptr<Unit> Cell::getUnit() {
    return unit;
}

void Cell::setUnit(std::shared_ptr<Unit> unit) {
    this->unit = unit;
}

std::shared_ptr<TerrainProxy> Cell::getTerrain() {
    return terrain;
}

void Cell::setTerrain(std::shared_ptr<TerrainProxy> terrain) {
    this->terrain = terrain;
}

std::shared_ptr<Entity> Cell::getEntity() {
    return entity;
}

void Cell::setEntity(std::shared_ptr<Entity> entity) {
    this->entity = entity;
}

Cell::Cell(const Cell &src) {
    unit =  src.unit;
    terrain =  src.terrain;
    entity =  src.entity;
}
