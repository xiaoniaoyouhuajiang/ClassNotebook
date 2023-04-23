#include "dwarffactory.h"

Unit* DwarfFactory::createUnit(Mediator* mediator)
{
    return new Dwarf(mediator);
}
