
#include "LandscapeFactory.h"

LandscapeFactory::LandscapeFactory()
{
    forest = new Forest;
    water = new Puddle;
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

Puddle *LandscapeFactory::getWater()
{
    return water;
}

Mountain *LandscapeFactory::getMountain()
{
    return mountain;
}