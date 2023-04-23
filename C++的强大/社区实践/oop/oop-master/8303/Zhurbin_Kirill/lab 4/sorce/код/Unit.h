#ifndef OOP1_UNIT_H
#define OOP1_UNIT_H

#include <string>
#include "Condition.h"
#include "SubjectObserve.h"


class Unit: public SubjectObserve{
public:
    Condition condition;
    char name;
    std::string character;
    Unit();
    void death();
};

#endif //OOP1_UNIT_H
