//
// Created by Alex on 21.03.2020.
//

#ifndef GAME_GAMECELL_H
#define GAME_GAMECELL_H


#include "../Base/Base.h"
#include "../Landscapes/Landscape.h"
#include "../NeutralObjects/NeutralObject.h"

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

    Landscape *getLanscape() const;

    NeutralObject *getNeutralObject() const;
};


#endif //GAME_GAMECELL_H
