#include "swordsmanfactory.h"


Unit* SwordsmanFactory::createUnit(Mediator* mediator)
{
    return new Swordsman(mediator);
}
