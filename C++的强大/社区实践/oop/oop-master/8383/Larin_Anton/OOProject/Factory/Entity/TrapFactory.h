//
// Created by anton on 5/28/20.
//

#ifndef OOPROJECT_TRAPFACTORY_H
#define OOPROJECT_TRAPFACTORY_H

#include "AbstractEntityFactory.h"

class TrapFactory: public AbstractEntityFactory {
public:
    TrapFactory(int dmgAmount);

    std::shared_ptr<GameObject> createObject(int x, int y, Devotion devotion) override;

private:
    int trapDmg;
};


#endif //OOPROJECT_TRAPFACTORY_H
