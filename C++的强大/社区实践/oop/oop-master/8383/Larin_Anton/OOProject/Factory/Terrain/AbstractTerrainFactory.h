//
// Created by anton on 5/26/20.
//

#ifndef OOPROJECT_ABSTRACTTERRAINFACTORY_H
#define OOPROJECT_ABSTRACTTERRAINFACTORY_H

#include "../AbstractFactory.h"

class AbstractTerrainFactory: public AbstractFactory {
public:
    AbstractTerrainFactory(int steepness);

protected:
    int steepness=2;
};


#endif //OOPROJECT_ABSTRACTTERRAINFACTORY_H
