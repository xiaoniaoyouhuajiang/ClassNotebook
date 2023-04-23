
#ifndef UNTITLED13_HOSPITAL_H
#define UNTITLED13_HOSPITAL_H


#include "NeutralObject.h"

class Hospital: public NeutralObject {


protected:

    void print(std::ostream &stream) const override{

        stream << "HP";

    }

public:

    void applyTo(Unit &unit) override {

        unit.heal(100*strategy->getUnitTypeFactor());

    }

};


#endif //UNTITLED13_HOSPITAL_H
