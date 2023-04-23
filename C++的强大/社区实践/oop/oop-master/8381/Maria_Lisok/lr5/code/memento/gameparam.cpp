#include "gameparam.h"
GameParam::GameParam(unsigned width, unsigned height, unsigned limit, vector<BaseParam*> bases, vector<NeutralParam*> neutrals, vector<LandscapeType> landscape):
    width(width), height(height), limit(limit), bases(bases),neutrals(neutrals), landscape(landscape)
{}

unsigned GameParam::getWidth() const
{
    return width;
}

unsigned GameParam::getHeight() const
{
    return height;
}

unsigned GameParam::getLimit() const
{
    return limit;
}

vector<BaseParam*> GameParam::getBases() const
{
    return bases;
}

vector<NeutralParam*> GameParam::getNeutrals() const
{
    return neutrals;
}

vector<LandscapeType> GameParam::getLandscape() const
{
    return landscape;
}
