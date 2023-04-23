//
// Created by Artem Butko on 19/05/2020.
//

#include "Refresh.h"

void Refresh::impact(Object* unit)
{
    unit->health.actHealed(200);
    unit->mana.actRecovered(200);
}
