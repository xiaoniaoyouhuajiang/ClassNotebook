//
// Created by shenk on 14.02.2020.
//

#include "Unit.h"

Unit::Unit(Unit *other) {

    armor = other->armor;
    weapon = other->weapon;
    health = other->health;

}
