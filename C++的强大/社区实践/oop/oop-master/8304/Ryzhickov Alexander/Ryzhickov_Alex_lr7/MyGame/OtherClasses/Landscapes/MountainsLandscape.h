//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_MOUNTAINSLANDSCAPE_H
#define GAME_MOUNTAINSLANDSCAPE_H


#include "Landscape.h"
namespace Landscapes {
    class MountainsLandscape : public Landscape {
        bool getInformationAboutLandscape() override;

        void setBonus(GameUnit::Unit *unit) override;
    };
}

#endif //GAME_MOUNTAINSLANDSCAPE_H
