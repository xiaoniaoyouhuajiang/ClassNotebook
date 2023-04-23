//
// Created by anton on 5/26/20.
//

#ifndef OOPROJECT_HOLLYFACTORY_H
#define OOPROJECT_HOLLYFACTORY_H

#include "AbstractTerrainFactory.h"

class HollyFactory: public AbstractTerrainFactory {
public:
    HollyFactory(int steepness, int healAmount);

    std::shared_ptr<GameObject> createObject(int x, int y, Devotion devotion) override;

private:
    int healAmount;

};


#endif //OOPROJECT_HOLLYFACTORY_H
