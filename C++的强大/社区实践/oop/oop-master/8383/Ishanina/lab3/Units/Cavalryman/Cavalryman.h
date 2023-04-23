//
// Created by Mila on 23.02.2020.
//

#ifndef UNTITLED_CAVALRYMAN_H
#define UNTITLED_CAVALRYMAN_H


#include "../Unit.h"

class Cavalryman: public Unit{
protected:
    //unsigned countSteps;
    char whatYouName() override = 0;
    ObjectInterface* copy() override = 0;

public:
    //Cavalryman();

};


#endif //UNTITLED_CAVALRYMAN_H
