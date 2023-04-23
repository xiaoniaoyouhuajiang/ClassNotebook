//
// Created by anton on 5/16/20.
//

#ifndef OOPROJECT_STEEPTERRAIN_H
#define OOPROJECT_STEEPTERRAIN_H

#include "Terrain.h"

class SteepTerrain:public Terrain {
public:
    SteepTerrain(int x, int y, int steepness);

private:
    CommonClass getObjectClass() override;
};


#endif //OOPROJECT_STEEPTERRAIN_H
