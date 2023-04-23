#ifndef OOP1_BASE_H
#define OOP1_BASE_H


#include <vector>
#include "Unit.h"
#include "CompositUnit.h"

class Field;

class Base: public Observer {
    friend class Field;
    friend class StatusBaseCommand;
    friend std::ostream& operator<< (std::ostream &out, const Base& base);
    friend class SnapshotField;
private:
    Field* field;
    int current;
    Adapter* adapter;
    CompositUnit* compositUnit;
    int countUnit;
    int BaseX, BaseY;
    int maxCountUnit, health;
    Base(Field* fileldint, int maxCountUnit, int health, int BaseX, int BaseY);
public:
    int numberBase;
    void update(SubjectObserve* subject);
    void removeUnit(Unit* unit);
    void printUnit();

    bool createUnit(char name, Mediator* mediator, Adapter* adapter);

    int getCapacityUnit();

    Unit *getUnit();

    bool wasAttack(int damage);

    bool setUnit(char name, int unitX, int unitY, int health, int attack, int armor, Mediator *mediator, Adapter *adapter);

    bool isDestroyed();
};


#endif //OOP1_BASE_H
