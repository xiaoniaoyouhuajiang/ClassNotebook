//
// Created by Artem Butko on 14/05/2020.
//

#ifndef OOP_NEW_LANDSCAPEFACTORY_H
#define OOP_NEW_LANDSCAPEFACTORY_H


#include "../../Landscape/Forest/Forest.h"
#include "../../Landscape/Mountain/Mountain.h"
#include "../../Landscape/Water/Water.h"

/*
 * LandscapeFactory -- фабрика объектов ландшафта (заместитель).
 */

class LandscapeFactory
{
public:
    LandscapeFactory();
    ~LandscapeFactory();

    Forest* getForest();
    Water* getWater();
    Mountain* getMountain();

private:
    Forest* forest;
    Water* water;
    Mountain* mountain;
};


#endif //OOP_NEW_LANDSCAPEFACTORY_H
