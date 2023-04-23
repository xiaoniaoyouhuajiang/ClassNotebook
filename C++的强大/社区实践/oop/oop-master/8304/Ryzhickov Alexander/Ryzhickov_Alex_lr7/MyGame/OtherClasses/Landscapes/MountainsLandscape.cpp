//
// Created by Alex on 21.03.2020.
//

#include "MountainsLandscape.h"

namespace Landscapes {
    bool MountainsLandscape::getInformationAboutLandscape() {
        return false;
    }

    void MountainsLandscape::setBonus(GameUnit::Unit *unit) {
        unit->setAttackBonus(0);
    }
}