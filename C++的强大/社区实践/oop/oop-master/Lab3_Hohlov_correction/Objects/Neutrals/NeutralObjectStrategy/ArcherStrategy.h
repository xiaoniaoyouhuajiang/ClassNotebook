
#ifndef UNTITLED13_ARCHERSTRATEGY_H
#define UNTITLED13_ARCHERSTRATEGY_H


#include "NeutralObjectStrategy.h"

class ArcherStrategy: public NeutralObjectStrategy {

public:
    int getUnitTypeFactor() override {
        return 1;
    }

};


#endif //UNTITLED13_ARCHERSTRATEGY_H
