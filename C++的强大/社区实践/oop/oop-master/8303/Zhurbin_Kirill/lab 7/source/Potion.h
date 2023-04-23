#ifndef OOP1_POTION_H
#define OOP1_POTION_H

#include "Unit.h"
#include "NeutralObject.h"

class Potion{
public:
    virtual void action(Unit* unit) = 0;
};

class PotionAction: public NeutralObject{
public:
    Potion* potion;
    PotionAction(){
        this->name = 'z';
    }
    PotionAction(Potion* potion): potion(potion){
    }

    void operator >>(Unit* unit) {
        potion->action(unit);
    }
};

class PotionTankman: public Potion{
    void action(Unit* unit) override {
        unit->condition.health += 20;
    }
};

class PotionShooter: public Potion{
    void action(Unit* unit) override {
        unit->condition.health += 30;
    }
};

class PotionSoldier: public Potion{
    void action(Unit* unit) override {
        unit->condition.health += 40;
    }
};

#endif //OOP1_POTION_H
