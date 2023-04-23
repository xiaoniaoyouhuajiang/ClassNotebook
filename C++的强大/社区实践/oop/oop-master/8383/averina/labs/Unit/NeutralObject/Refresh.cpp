
#include "Refresh.h"

void Refresh::impact(Object* unit)
{
    unit->health.actHealed(200);
    unit->mana.actRecovered(200);
}