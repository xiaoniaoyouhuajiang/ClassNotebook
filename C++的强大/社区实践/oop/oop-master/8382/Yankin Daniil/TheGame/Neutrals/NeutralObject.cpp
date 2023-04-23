#include "NeutralObject.h"
#include "Unit/UnitHeader.h"


bool HealOffice::operator>>(IUnit& unit) {
    unit.fullHeal();
    return true;
}


bool DamageOffice::operator>>(IUnit& unit) {
    bool alive = unit.takeDamage(40);
    return alive;
}


bool ArmorOffice::operator>>(IUnit& unit) {
    unit.armorModification(2);
    return true;
}


bool MovementOffice::operator>>(IUnit& unit) {
    unit.renewMovePoints();
    return true;
}
