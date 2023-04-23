//
// Created by Artem Butko on 19/05/2020.
//

#include "HealthDown.h"

void HealthDown::impact(Object* unit)
{
    unit->health.actDamaged(150);
}
