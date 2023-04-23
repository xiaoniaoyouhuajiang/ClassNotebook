//
// Created by Mila
//

#ifndef UNTITLED_STRATEGY_H
#define UNTITLED_STRATEGY_H

#include "Context.h"
#include "MedicalKit.h"
#include "PowerPotion.h"
#include "Shild.h"

class Strategy: public Context{
public:
    virtual void useStrategy(Unit* unit) override {
        if(neutralObject->whatYouName() == '+')
        {
            (*neutralObject) + unit->getHealthForUpdate();
        }
        if(neutralObject->whatYouName() == '&')
        {
            (*neutralObject) + unit->getDamageForUpdate();
        }
        if(neutralObject->whatYouName() == '@')
        {
            if(unit->whatYouName() != 'E' && unit->whatYouName() != 'M' && unit->whatYouName() != 'G')//щит увеличивает броню всем, кроме эльфа, мага и гнома
                (*neutralObject) + unit->getArmorForUpdate();
        }

    }
    virtual void setStrategy(NeutralObjectInterface* neutralObject) override {
        Strategy::neutralObject = neutralObject;

    }
};

#endif //UNTITLED_STRATEGY_H
