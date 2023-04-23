#ifndef OOP1_MEDIATOR_H
#define OOP1_MEDIATOR_H

#include "Field.h"

class Mediator{
public:
    Mediator(Field* field);

    void attack(Unit* unit, int x, int y);
    void setField(Field *field);
private:
    Field* field;


};

#endif //OOP1_MEDIATOR_H
