#include "harpyfactory.h"


Unit* HarpyFactory::createUnit(Mediator* mediator)
{
    return new Harpy(mediator);
}
