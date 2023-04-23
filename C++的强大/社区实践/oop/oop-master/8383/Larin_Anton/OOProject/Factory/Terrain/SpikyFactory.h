//
// Created by anton on 5/26/20.
//

#ifndef OOPROJECT_SPIKYFACTORY_H
#define OOPROJECT_SPIKYFACTORY_H

#include "AbstractTerrainFactory.h"

class SpikyFactory: public AbstractTerrainFactory {
public:
    SpikyFactory(int steepness, int damage);

    std::shared_ptr<GameObject> createObject(int x, int y, Devotion devotion) override;

private:
    int damage;
};


#endif //OOPROJECT_SPIKYFACTORY_H
