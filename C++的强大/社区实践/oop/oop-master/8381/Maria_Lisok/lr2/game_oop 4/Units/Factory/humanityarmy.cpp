#include "humanityArmy.h"


Arrow *HumanityArmy::createArrow()
{
    return new Archer();
}

Cavelry *HumanityArmy::createCavelry()
{
    return new Knigth();
}

Infantry *HumanityArmy::createInfantry()
{
    return new Swardman();
}
