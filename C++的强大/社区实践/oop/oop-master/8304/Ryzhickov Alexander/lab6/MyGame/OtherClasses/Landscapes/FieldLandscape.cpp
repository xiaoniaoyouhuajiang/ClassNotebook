//
// Created by Alex on 21.03.2020.
//

#include "FieldLandscape.h"
#include "typeinfo"
#include "../../Units/HeavyInfantry/HeavyInfantry.h"

bool FieldLandscape::getInformationAboutLandscape() {
    return true;
}

void FieldLandscape::setBonus(Unit *unit) {
    if (dynamic_cast<HeavyInfantry *>(unit) != nullptr) {
        unit->setAttackBonus(25);
    } else {
        unit->setAttackBonus(0);
    }
}
