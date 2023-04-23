//
// Created by anton on 5/25/20.
//

#ifndef OOPROJECT_ABSTRACTUNITFACTORY_H
#define OOPROJECT_ABSTRACTUNITFACTORY_H

#include <memory>
#include <cassert>

#include "../AbstractFactory.h"


class Base;
class Unit;

class AbstractUnitFactory:public AbstractFactory{
public:
    AbstractUnitFactory(int health, int armour, float dmgmul, int abPower, int abRange, int mbAgility, int mbRange);
    void setBase(std::shared_ptr<Base> base,Devotion devotion);
    void onUnitCreate(std::shared_ptr<Unit> unit);

protected:
    int health = 100;
    int armour = 100;
    float dmgmul = 1;
    int abPower=10;
    int abRange=2;
    int mbAgility=5;
    int mbRange=5;

    std::shared_ptr<Base> lightBase;
    std::shared_ptr<Base> darkBase;

};


#endif //OOPROJECT_ABSTRACTUNITFACTORY_H
