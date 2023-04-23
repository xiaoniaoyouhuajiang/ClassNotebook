//
// Created by Mila on 23.02.2020.
//

#ifndef UNTITLED_ARTILLERIST_H
#define UNTITLED_ARTILLERIST_H


#include "../Unit.h"

class Artillerist : public Unit{

protected:
    //unsigned countShots;
    char whatYouName() override = 0;
    ObjectInterface* copy() override = 0;

public:
    //Artillerist();//конструктор

};


#endif //UNTITLED_ARTILLERIST_H

