//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_FIELDLANDSCAPE_H
#define GAME_FIELDLANDSCAPE_H


#include "Landscape.h"
namespace Landscapes {
    class FieldLandscape : public Landscape {
        bool getInformationAboutLandscape() override;

        void setBonus(GameUnit::Unit *unit) override;
    };
}

#endif //GAME_FIELDLANDSCAPE_H
