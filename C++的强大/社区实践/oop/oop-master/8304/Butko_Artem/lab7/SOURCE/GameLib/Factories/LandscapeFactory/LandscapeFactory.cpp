//
// Created by Artem Butko on 14/05/2020.
//

#include "LandscapeFactory.h"

LandscapeFactory::LandscapeFactory()
{
    forest = new Forest;
    water = new Water;
    mountain = new Mountain;
}

LandscapeFactory::~LandscapeFactory()
{
    delete forest;
    delete water;
    delete mountain;
}

Forest *LandscapeFactory::getForest()
{
    return forest;
}

Water *LandscapeFactory::getWater()
{
    return water;
}

Mountain *LandscapeFactory::getMountain()
{
    return mountain;
}
