
#include "../../Object/Object.h"
#include "HelthDown.h"

void HealthDown::impact(Object* unit)
{
    unit->health.actDamaged(150);

}