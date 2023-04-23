//
// Created by Alex on 08.03.2020.
//

#ifndef MYGAME_FIELDLANDSCAPE_H
#define MYGAME_FIELDLANDSCAPE_H


#include "Landscape.h"

class FieldLandscape: public Landscape {
public:
    FieldLandscape();
    bool getInformationAboutLandscape() override;
    int getBonus(kindUnit kindUnit) override;
};


#endif //MYGAME_FIELDLANDSCAPE_H
