//
// Created by anton on 5/28/20.
//

#ifndef OOPROJECT_HEALFACTORY_H
#define OOPROJECT_HEALFACTORY_H

#include "AbstractEntityFactory.h"

class HealFactory: public AbstractEntityFactory {
public:
    HealFactory(int healAmount);

    std::shared_ptr<GameObject> createObject(int x, int y, Devotion devotion) override;

private:
    int healAmount;
};


#endif //OOPROJECT_HEALFACTORY_H
