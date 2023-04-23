#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <iostream>
#include "Units/unit.h"
#include "Landscapes/landscape.h"
#include "Landscapes/forests.h"
#include "Landscapes/mountains.h"
#include "Landscapes/rivers.h"
#include "base.h"
#include "observer.h"
#include "NeutralObject/neutralobject.h"
#include "NeutralObject/poison.h"
#include "NeutralObject/weapon.h"
#include "NeutralObject/armor.h"
#include "NeutralObject/medicine.h"
#include "loggerproxy.h"
#include "fieldsnapshot.h"

class Mediator;

struct Point
{
    int x, y;
    Unit* unit;
    Landscape* landscape;
    Base* base;
    NeutralObject* nObject;
};

class GameField : public Observer
{
public:
    GameField(int x = 0, int y = 0, int maxCount = 0, int isCorrectCreated = 0);
    GameField(const GameField &);
    GameField(GameField &&);
    bool canStand(std::string, int, int);
    bool createUnit(std::string, Base*, Mediator*);
    Unit* createUnit(int ,int, std::string, int, Mediator*);
    void deleteUnit(Subject*);
    void moveUnitLeft(Unit*, Base*);
    void moveUnitRight(Unit*, Base*);
    void moveUnitUp(Unit*, Base*);
    void moveUnitDown(Unit*, Base*);
    void printBase(Base*);
    Point* findUnit(Unit*);
    void printAll() const;
    void setBase(int, int, int, int);
    void setUnit(Unit*, int, int, Base*);
    void update(Subject* subject) override;
    FieldSnapshot* getSnapshot();
    GameField& operator=(const GameField&);
    int getX();
    int getY();
    bool isBasesCreated();

    bool isCorrectCreated;

    friend class Iterator;
    friend class Mediator;
    friend class CreateUnitCommand;
    friend class CreateUnitHandler;
    friend class MoveUnitHandler;
    friend class MoveUnitCommand;
    friend class BaseStatusHandler;
    friend class AttackHandler;
    friend class Rule1;
    friend class Rule2;
    friend std::ostream& operator<< (std::ostream&, const GameField&);

private:
    int x;
    int y;
    int unitCount;
    int maxCount;
    Base* base1;
    Base* base2;
    Base* base3;
    Point*** pointsMap;     //Двумерный массив указателей на ячейки Point на поле
    const std::vector <std::string> unitsNames = {"Flatbow", "Longbow", "Dragoon", "Hussar", "Swordsman", "Spearman"};

    void moveUnit(Unit*, int, int, Base*);
};

#endif // GAMEFIELD_H
