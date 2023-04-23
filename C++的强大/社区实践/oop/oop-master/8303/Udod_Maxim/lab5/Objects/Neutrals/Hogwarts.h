//
// Created by shenk on 01.03.2020.
//

#ifndef UNTITLED13_HOGWARTS_H
#define UNTITLED13_HOGWARTS_H


#include "NeutralObject.h"
#include "../Units/Wizard/Voldemort.h"

class Hogwarts: public NeutralObject {


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


#endif //UNTITLED13_HOGWARTS_H
