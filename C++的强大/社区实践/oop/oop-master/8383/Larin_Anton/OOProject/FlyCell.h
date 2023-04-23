//
// Created by anton on 5/31/20.
//

#ifndef OOPROJECT_FLYCELL_H
#define OOPROJECT_FLYCELL_H

#include <memory>
#include "Stats.h"

struct FlyCell {
    friend class Mediator;

private:
    std::shared_ptr<GameObjectFlyWeight> unit;
    std::shared_ptr<GameObjectFlyWeight> terrain;
    std::shared_ptr<GameObjectFlyWeight> entity;
public:
    GameObjectFlyWeight *getUnit() const;

    GameObjectFlyWeight *getTerrain() const;

    GameObjectFlyWeight *getEntity() const;

    void setUnit(GameObjectFlyWeight *unit);

    void setTerrain(GameObjectFlyWeight *terrain);

    void setEntity(GameObjectFlyWeight *entity);


};


#endif //OOPROJECT_FLYCELL_H
