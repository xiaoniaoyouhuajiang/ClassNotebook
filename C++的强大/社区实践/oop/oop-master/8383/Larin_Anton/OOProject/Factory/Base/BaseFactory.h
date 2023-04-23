//
// Created by anton on 5/27/20.
//

#ifndef OOPROJECT_BASEFACTORY_H
#define OOPROJECT_BASEFACTORY_H

#include "../AbstractFactory.h"

#include "../../GameObject/Base/Base.h"
//class Base;

class BaseFactory: public AbstractFactory {
public:
    //BaseFactory(int lim);

    BaseFactory(int lim, int baseHealth, int baseArmour, int baseDmgmul);

    std::shared_ptr<Base> createBase(int x, int y, Devotion devotion);

    std::shared_ptr<GameObject> createObject(int x, int y, Devotion devotion) override;

private:
    int lim;
    int baseHealth;
    int baseArmour;
    int baseDmgmul;


};


#endif //OOPROJECT_BASEFACTORY_H
