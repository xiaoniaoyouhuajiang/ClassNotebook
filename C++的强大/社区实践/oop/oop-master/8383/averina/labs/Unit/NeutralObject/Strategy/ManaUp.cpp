
#include "ManaUp.h"


void ManaUp::impact(Object* unit)
{
    unit->mana.actRecovered(200);
}