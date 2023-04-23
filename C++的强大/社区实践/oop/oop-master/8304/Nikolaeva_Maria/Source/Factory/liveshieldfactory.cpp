#include "liveshieldfactory.h"


Unit* LiveShieldFactory::createUnit(Mediator* mediator)
{
    return new LiveShield(mediator);
}
