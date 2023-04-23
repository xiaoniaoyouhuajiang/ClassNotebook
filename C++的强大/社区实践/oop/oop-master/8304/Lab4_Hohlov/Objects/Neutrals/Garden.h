

#ifndef UNTITLED13_GARDEN_H
#define UNTITLED13_GARDEN_H

#include "NeutralObject.h"
#include "NeutralObjectStrategy/NeutralObjectStrategy.h"

class Garden: public NeutralObject {


protected:

    void print(std::ostream &stream) const override{

        stream << "G";

    }

public:

    void applyTo(Unit &unit) override {

        unit.heal(10*strategy->getUnitTypeFactor());

    }

};


#endif //UNTITLED13_GARDEN_H
