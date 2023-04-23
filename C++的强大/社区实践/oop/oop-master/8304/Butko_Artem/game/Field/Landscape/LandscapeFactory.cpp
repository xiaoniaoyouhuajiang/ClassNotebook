//

//

#include "LandscapeFactory.h"

LandscapeFactory::LandscapeFactory()
{
    mountain_ = new Mountain;
    field_ = new Field;
    forest_ = new Forest;
}

LandscapeFactory::~LandscapeFactory()
{
    delete mountain_;
    delete field_;
    delete forest_;
}

Field *LandscapeFactory::getFieldLandscape()
{
    return field_;
}

Forest *LandscapeFactory::getForestLandscape()
{
    return forest_;
}

Mountain *LandscapeFactory::getMountainLandscape()
{
    return mountain_;
}


