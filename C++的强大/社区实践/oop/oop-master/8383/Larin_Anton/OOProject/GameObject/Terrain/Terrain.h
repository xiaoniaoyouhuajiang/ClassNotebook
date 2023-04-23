//
// Created by anton on 5/16/20.
//

#ifndef OOPROJECT_TERRAIN_H
#define OOPROJECT_TERRAIN_H


#include "../GameObject.h"
#include "../../Stats.h"


class Terrain: public GameObject {
    friend class TerrainProxy;
public:
    Terrain(int x, int y, CommonClass objectClass, TerrainType terrainType, int steepness);

    virtual void restep(std::shared_ptr<GameObject> sbj) override;

    virtual void act(std::shared_ptr<GameObject> obj) override;

    virtual void react(std::shared_ptr<GameObject> sbj) override;

    virtual void step(std::shared_ptr<GameObject> obj) override;

    virtual bool canStep(int x, int y) override;

    virtual bool canAct(int x, int y) override;

    virtual int getSteepness();

protected:
    TerrainType terrainType;
    int steepness;

};


#endif //OOPROJECT_TERRAIN_H
