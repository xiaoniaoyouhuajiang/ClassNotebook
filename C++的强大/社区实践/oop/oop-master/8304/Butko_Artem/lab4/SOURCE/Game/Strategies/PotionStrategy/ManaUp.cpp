//
// Created by Artem Butko on 19/05/2020.
//

#include "ManaUp.h"

void ManaUp::impact(Object* unit)
{
    unit->mana.actRecovered(200);
}
