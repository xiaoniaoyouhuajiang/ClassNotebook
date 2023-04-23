#ifndef OOP1_UNIT_H
#define OOP1_UNIT_H

#include <string>
#include "Condition.h"
#include "SubjectObserve.h"
#include "UnitMediator.h"
#include "Logger.h"
#include "Adapter.h"


class Unit: public SubjectObserve, public UnitMediator{
    Adapter* adapter;
public:
    Condition condition;
    char name;
    std::string character;
    Unit();
    void death();

    void wasAttack(int damage);

    void setAdapter(Adapter *adapter);
};

#endif //OOP1_UNIT_H
