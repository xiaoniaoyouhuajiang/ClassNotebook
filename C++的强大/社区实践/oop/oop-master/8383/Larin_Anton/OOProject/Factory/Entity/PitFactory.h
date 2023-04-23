//
// Created by anton on 5/28/20.
//

#ifndef OOPROJECT_PITFACTORY_H
#define OOPROJECT_PITFACTORY_H

#include "AbstractEntityFactory.h"

class PitFactory: public AbstractEntityFactory {
public:
    PitFactory(int pitHealth, int dmgAmount);

    std::shared_ptr<GameObject> createObject(int x, int y, Devotion devotion) override;

private:
    int pitHealth;
    int pitDmg;
};


#endif //OOPROJECT_PITFACTORY_H
