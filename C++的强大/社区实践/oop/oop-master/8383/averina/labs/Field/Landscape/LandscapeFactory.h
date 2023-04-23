//
// Created by olyaave on 01.06.2020.
//

#ifndef OOP_LANDSCAPEFACTORY_H
#define OOP_LANDSCAPEFACTORY_H


#include "Puddle.h"
#include "Mountain.h"
#include "Forest.h"

/*
 * LandscapeFactory -- фабрика объектов ландшафта (заместитель).
 */

class LandscapeFactory
{
public:
    LandscapeFactory();
    ~LandscapeFactory();

    Forest* getForest();
    Puddle* getWater();
    Mountain* getMountain();

private:
    Forest* forest;
    Puddle* water;
    Mountain* mountain;
};


#endif //OOP_LANDSCAPEFACTORY_H
