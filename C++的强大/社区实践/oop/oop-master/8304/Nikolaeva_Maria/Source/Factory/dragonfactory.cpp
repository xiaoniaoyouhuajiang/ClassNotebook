#include "dragonfactory.h"


Unit* DragonFactory::createUnit(Mediator* mediator)
{
    return new Dragon(mediator);
}
