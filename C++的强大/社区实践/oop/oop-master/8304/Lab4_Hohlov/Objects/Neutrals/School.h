
#ifndef UNTITLED13_SCHOOL_H
#define UNTITLED13_SCHOOL_H


#include "NeutralObject.h"
#include "../Units/Wizard/StormMage.h"

class School: public NeutralObject {


protected:

    void print(std::ostream &stream) const override{

        stream << "HW";

    }

public:

    void applyTo(Unit &unit) override {

        Voldemort voldemort;
        unit = voldemort;

    }

};


#endif //UNTITLED13_SCHOOL_H
