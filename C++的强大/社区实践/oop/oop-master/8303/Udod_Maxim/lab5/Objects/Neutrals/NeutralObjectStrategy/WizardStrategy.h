//
// Created by shenk on 01.03.2020.
//

#ifndef UNTITLED13_WIZARDSTRATEGY_H
#define UNTITLED13_WIZARDSTRATEGY_H


#include "NeutralObjectStrategy.h"

class WizardStrategy: public NeutralObjectStrategy {

public:
    int getUnitTypeFactor() override {
        return 2;
    }

};


#endif //UNTITLED13_WIZARDSTRATEGY_H
