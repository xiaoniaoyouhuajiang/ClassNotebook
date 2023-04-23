#include "river.h"
string River::getLandscapeType()
{
    return "river";
}

bool River::canStand()
{
    return true;
}

LandscapeType River::getLandscapeTypeEnum()
{
    return RIVER;
}
