#include "creaturesArmy.h"


Arrow *CreaturesArmy::createArrow()
{
    return new Shaman();
}

Cavelry *CreaturesArmy::createCavelry()
{
    return new Rider();
}

Infantry *CreaturesArmy::createInfantry()
{
    return new Ork();
}
