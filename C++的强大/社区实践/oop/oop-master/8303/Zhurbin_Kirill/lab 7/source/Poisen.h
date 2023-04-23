#ifndef OOP1_POISEN_H
#define OOP1_POISEN_H

#include "NeutralObject.h"
#include "Unit.h"


class Poisen{
public:
    virtual void action(Unit* unit) = 0;
};

class PoisenAction: public NeutralObject{
public:
    Poisen* poisen;
    PoisenAction(){
        this->name = 'p';
    }
    PoisenAction(Poisen* poisen): poisen(poisen){
    }

    void operator >> (Unit* unit){
        poisen->action(unit);
    }


};

class PoisenTankman: public Poisen{
    void action(Unit* unit) override {
        unit->condition.health -= 20;
    }
};

class PoisenShooter: public Poisen{
    void action(Unit* unit) override {
        unit->condition.health -= 30;
    }
};

class PoisenSoldier: public Poisen{
    void action(Unit* unit) override {
        unit->condition.health -= 40;
    }
};

#endif //OOP1_POISEN_H
