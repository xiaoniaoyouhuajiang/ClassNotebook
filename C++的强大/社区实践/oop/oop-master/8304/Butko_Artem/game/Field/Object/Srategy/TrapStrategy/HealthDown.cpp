



#include "HealthDown.h"

void HealthDown::unitImpact(Unit *unit_)
{
    unit_->health.actDamaged(50);
}
