
#include "Damn.h"

void Damn::impact(Object* unit)
{
    unit->health.set(1);
    unit->damage.set(1,1,1);
}