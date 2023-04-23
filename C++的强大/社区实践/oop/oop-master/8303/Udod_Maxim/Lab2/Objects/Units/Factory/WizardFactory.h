//
// Created by shenk on 16.02.2020.
//

#ifndef UNTITLED13_WIZARDFACTORY_H
#define UNTITLED13_WIZARDFACTORY_H


#include "UnitFactory.h"
#include "../Wizard/Voldemort.h"
#include "../Wizard/FireMage.h"

class WizardFactory: public UnitFactory {

public:

    Voldemort *createStrong(){ return new Voldemort(); }
    FireMage *createWeack(){ return new FireMage(); }

};


#endif //UNTITLED13_WIZARDFACTORY_H
