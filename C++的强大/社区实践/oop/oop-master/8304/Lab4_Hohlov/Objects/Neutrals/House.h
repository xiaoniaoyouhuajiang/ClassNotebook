

#ifndef UNTITLED13_HOUSE_H
#define UNTITLED13_HOUSE_H


#include "NeutralObject.h"

class House: public NeutralObject {

protected:

    void print(std::ostream &stream) const override{

        stream << "HS";

    }

public:

    void applyTo(Unit &unit) override {

        unit.heal(50*strategy->getUnitTypeFactor());

    }

};


#endif //UNTITLED13_HOUSE_H
