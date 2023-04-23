//
// Created by Mila on 23.02.2020.
//

#ifndef UNTITLED_CAVALRYMAN_H
#define UNTITLED_CAVALRYMAN_H


#include "../Unit.h"

class Cavalryman: public Unit{
protected:

    void whatYouName() override = 0;
    ObjectInterface* copy() override = 0;


};


#endif //UNTITLED_CAVALRYMAN_H
