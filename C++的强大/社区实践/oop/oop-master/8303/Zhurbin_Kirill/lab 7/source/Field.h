#ifndef OOP1_FIELD_H
#define OOP1_FIELD_H

#include <iostream>
#include "Unit.h"
#include "Landscape.h"
#include "Wall.h"
#include "Water.h"
#include "Ground.h"
#include "Base.h"
#include "NeutralObject.h"
#include "SnapshotField.h"


class Field{
    friend std::ostream& operator<< (std::ostream &out, const Field& field);
private:
    int lenghtX, lengthY;
    int maxCountObject;
    int countUnit;
    Cell ***mapCell;
    Adapter* adapter;
public:
    Field& operator= (const Field& field);
    Base* base1;
    Base* base2;
    Base* base3;

    friend class Iterator;
    friend class Mediator;
    friend class SetBaseHandler;

    Field(int x, int y, int maxCountObject, Adapter* adapter);

    Field(const Field &field);

    Field(Field &&field);

    bool addUnit(Unit *unit, int, int);

    void removeUnit(Unit *unit);

    void printAll() const;

    void moveUnit(Unit *unit, int x, int y) ;

    void moveUnitLeft(Unit *unit);

    void moveUnitUp(Unit *unit);

    void moveUnitRight(Unit *unit);

    void moveUnitDown(Unit *unit);

    Cell *findUnit(Unit *unit);

    void addLandscape() const;

    void printLandscape() const;

    Base* createBase(int BaseX, int BaseY, int maxCountUnit, int health, Adapter* adapter);

    void addNeutral(int NeutralX, int NeutralY, char name) const;

    void printNeutral() const;

    SnapshotField *createSnap(std::string mode);

    Adapter *getAdapter();
};
#endif //OOP1_FIELD_H
