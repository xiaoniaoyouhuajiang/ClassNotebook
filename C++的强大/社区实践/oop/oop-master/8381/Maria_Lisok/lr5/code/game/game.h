#ifndef GAME_H
#define GAME_H

#include "playingfield.h"
#include "gamemediator.h"
#include "NeutralObj/armor.h"
#include "NeutralObj/medicine.h"
#include "NeutralObj/poison.h"
#include "NeutralObj/weapon.h"
#include "memento/memento.h"

#include "memento/gamememento.h"

class Game
{
public:
    Game(unsigned x, unsigned y, unsigned limit);
    void createBase(int maxUnitsCount, int health, int xx, int yy, int baseNumb);
    void createNeutral(NeutralType obj,unsigned x, unsigned y);
    void addUnit(Unit *unit, Base *base);
    void deleteUnit(Unit *unit, Base *base);
    Base* getBaseByNum(int num);

    std::vector<Base *> getBases() const;

    std::vector<Unit *> getUnits() const;

    PlayingField *getField() const;

    void restoreMemento(Memento* memento);
    GameMemento* readMemento(string name);


private:
    PlayingField* field;
    std::vector<Base*> bases;
    AttackMediator* units;
    GameMediator* gameMediator;
};

#endif // GAME_H
