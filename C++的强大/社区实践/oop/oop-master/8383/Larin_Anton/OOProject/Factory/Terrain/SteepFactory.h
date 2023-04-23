//
// Created by anton on 5/26/20.
//

#ifndef OOPROJECT_STEEPFACTORY_H
#define OOPROJECT_STEEPFACTORY_H

#include "AbstractTerrainFactory.h"

class SteepFactory: public AbstractTerrainFactory {
public:
    SteepFactory(int steepness, int enhancedSteepness);

    std::shared_ptr<GameObject> createObject(int x, int y, Devotion devotion) override;

private:
    int enhancedSteepness;

};


#endif //OOPROJECT_STEEPFACTORY_H
