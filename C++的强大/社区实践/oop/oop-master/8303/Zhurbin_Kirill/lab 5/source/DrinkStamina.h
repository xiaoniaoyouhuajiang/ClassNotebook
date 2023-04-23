#ifndef OOP1_DRINKSTAMINA_H
#define OOP1_DRINKSTAMINA_H

#include "NeutralObject.h"


class DrinkStamina{
public:
    virtual void action(Unit* unit) = 0;
};

class DrinkStaminaAction: public NeutralObject{
public:
    DrinkStamina* drinkStamina;

    DrinkStaminaAction(){
        this->name = 'a';
    }
    DrinkStaminaAction(DrinkStamina* drinkStamina): drinkStamina(drinkStamina){
    }

    void operator>>(Unit* unit){
        drinkStamina->action(unit);
    }
};

class DrinkStaminaTankman: public DrinkStamina{
    void action(Unit* unit) override {
        unit->condition.armor += 20;
    }
};

class DrinkStaminaShooter: public DrinkStamina{
    void action(Unit* unit) override {
        unit->condition.armor += 15;
    }
};

class DrinkStaminaSoldier: public DrinkStamina{
    void action(Unit* unit) override {
        unit->condition.armor += 10;
    }
};

#endif //OOP1_DRINKSTAMINA_H
