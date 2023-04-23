#ifndef OOP1_DRINKSTRONG_H
#define OOP1_DRINKSTRONG_H

#include "NeutralObject.h"

class DrinkStrong{
public:
    virtual void action(Unit* unit) = 0;
};

class DrinkStrongAction: public NeutralObject{
public:
    DrinkStrong* drinkStrong;
    DrinkStrongAction(){
        this->name = 's';
    }
    DrinkStrongAction(DrinkStrong* drinkStrong): drinkStrong(drinkStrong){
    }

    void operator>>(Unit* unit){
        drinkStrong->action(unit);
    }
};

class DrinkStrongTankman: public DrinkStrong{
    void action(Unit* unit) override {
        unit->condition.attack += 20;
    }
};

class DrinkStrongShooter: public DrinkStrong{
    void action(Unit* unit) override {
        unit->condition.attack += 15;
    }
};

class DrinkStrongSoldier: public DrinkStrong{
    void action(Unit* unit) override {
        unit->condition.attack += 10;
    }
};

#endif //OOP1_DRINKSTRONG_H
