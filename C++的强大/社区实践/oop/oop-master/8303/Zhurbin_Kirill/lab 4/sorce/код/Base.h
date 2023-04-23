#ifndef OOP1_BASE_H
#define OOP1_BASE_H


#include <vector>
#include "Unit.h"
#include "CompositUnit.h"

class Field;

class Base: public Observer {
    friend class Field;
private:
    int BaseX, BaseY;
    Field* field;
    CompositUnit* compositUnit;
    int maxCountUnit, health, countUnit;
    Base(Field* fileldint, int maxCountUnit, int health, int BaseX, int BaseY);
public:
    void update(SubjectObserve* subject);
    void removeUnit(Unit* unit);
    void printUnit();

    void createUnit(char name);
};


#endif //OOP1_BASE_H
