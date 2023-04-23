//
// Created by anton on 5/16/20.
//

#ifndef OOPROJECT_SPIKYTERRAIN_H
#define OOPROJECT_SPIKYTERRAIN_H

#include "Terrain.h"

class SpikyTerrain: public Terrain {
public:
    SpikyTerrain(int x, int y, int steepness, int damage);

    CommonClass getObjectClass() override;

private:
    int damage;
    void restep(std::shared_ptr<GameObject> sbj) override;

};


#endif //OOPROJECT_SPIKYTERRAIN_H
