#include "mountain.h"
string Mountain::getLandscapeType()
{
    return "mountain";
}
bool Mountain::canStand()
{
    return false;
}

LandscapeType Mountain::getLandscapeTypeEnum()
{
    return MOUNTAIN;
}
