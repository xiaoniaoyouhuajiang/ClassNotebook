//
// Created by anton on 5/16/20.
//

#ifndef OOPROJECT_HOLLYTERRAIN_H
#define OOPROJECT_HOLLYTERRAIN_H

#include "Terrain.h"

class HollyTerrain: public Terrain {
public:
    HollyTerrain(int x, int y, int amount);

    void restep(std::shared_ptr<GameObject> sbj) override;

private:
    CommonClass getObjectClass() override;

private:
    int amount;
};


#endif //OOPROJECT_HOLLYTERRAIN_H
