//
// Created by mensch on 15.03.2020.
//

#ifndef OOP_LABS_WIZARDFACTORY_H
#define OOP_LABS_WIZARDFACTORY_H


#include "UnitFactory.h"
#include "../Wizards/Druid.h"
#include "../Wizards/Archmage.h"

class WizardFactory : public UnitFactory{
public:
    Druid* createCommon() override {return new Druid;}
    Archmage* createStrong() override {return new Archmage;}
};


#endif //OOP_LABS_WIZARDFACTORY_H
