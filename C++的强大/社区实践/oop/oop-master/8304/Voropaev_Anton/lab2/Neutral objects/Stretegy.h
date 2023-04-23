#ifndef OOP_STRETEGY_H
#define OOP_STRETEGY_H

#include "../Unit.h"

struct Strategy {
    virtual void change_attribute(Unit* unit, int n) = 0;
};

struct strategy_dmg : Strategy{
    void change_attribute(Unit* unit, int n) final;
};

struct strategy_armor : Strategy{
    void change_attribute(Unit* unit, int n) final;
};

struct strategy_health : Strategy {
    void change_attribute(Unit *unit, int n) final;
};


#endif //OOP_STRETEGY_H
