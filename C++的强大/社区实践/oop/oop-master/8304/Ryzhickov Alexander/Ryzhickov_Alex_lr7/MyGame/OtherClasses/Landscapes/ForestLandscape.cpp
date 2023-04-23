//
// Created by Alex on 21.03.2020.
//

#include "ForestLandscape.h"
#include "typeinfo"
#include "../../Units/RangedUnits/RangedUnit.h"
namespace Landscapes {
    bool ForestLandscape::getInformationAboutLandscape() {
        return true;
    }

    void ForestLandscape::setBonus(GameUnit::Unit *unit) {
        if (dynamic_cast<GameUnit::RangedUnit *>(unit) != nullptr) {
            unit->setAttackBonus(25);
        } else {
            unit->setAttackBonus(0);
        }
    }
}
