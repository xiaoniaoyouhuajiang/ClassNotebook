//
// Created by Alex on 02.03.2020.
//

#ifndef MYGAME_GAMECELL_H
#define MYGAME_GAMECELL_H


#include "../Units/Unit.h"
#include "Landscapes/Landscape.h"
#include "NeutralObjects/NeutralObject.h"

class GameCell {
private:
    Base *base;
    Unit *unit;
    Landscape *lanscape;
    NeutralObject *neutralObject;
public:
    GameCell();

    int numer;

    void setUnit(Unit *unit);

    void setNeutralObject(NeutralObject *neutralObject);

    void setLanscape(Landscape *lanscape);

    void deleteUnit();

    Unit *getUnit() const;

    void setBase(Base *base);
};


#endif //MYGAME_GAMECELL_H
