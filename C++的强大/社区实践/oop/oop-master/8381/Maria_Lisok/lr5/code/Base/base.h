#ifndef BASE_H
#define BASE_H

#include "compositeUnit.h"
#include "Units/Factory/creaturesArmy.h"
#include "Units/Factory/humanityArmy.h"
#include "game/gamemediator.h"
#include "enums.h"

#include <createmediator.h>
class Base : public Observer
{
public:
    Base(int, int, int, int, int);

    int getBaseNumb() const;
    int getX() const;
    int getY() const;
    int getUnitCount() const;
    int getMaxCount() const;
    int getHealth() const;

    Unit* createUnit(UnitsType type);
    Unit* createUnit(string type);
    Unit* createUnit(string type, int posX, int posY);
    void addUnit(Unit* u);
    void deleteUnit(Subject*);
    Unit* getCurrUnit();
    bool getDamage(int numb);
    void update(Subject *);
    void setGameMediator(GameMediator* val);
    CompositeUnit *getUnits() const;

    void setCreateMediator(CreateMediator *value);

    CreateMediator *getCreateMediator() const;

    int getUnitCurr() const;

private:
    Unit* makeUnit(string type, int x, int y);
    int baseNumb;
    int unitCount;
    const int maxCount;
    int health;
    const int x, y;
    CompositeUnit* units;
    int unitCurr;
    GameMediator* gameMediator;
    CreateMediator* createMediator;
};

#endif // BASE_H
