#include "archerfactory.h"


Unit* ArcherFactory::createUnit(Mediator* mediator)
{
    return new Archer(mediator);
}
