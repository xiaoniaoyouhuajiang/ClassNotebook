//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_FIELDLANDSCAPE_H
#define GAME_FIELDLANDSCAPE_H


#include "Landscape.h"

class FieldLandscape : public Landscape {
    bool getInformationAboutLandscape() override;
    void setBonus(Unit *unit) override;
};


#endif //GAME_FIELDLANDSCAPE_H
