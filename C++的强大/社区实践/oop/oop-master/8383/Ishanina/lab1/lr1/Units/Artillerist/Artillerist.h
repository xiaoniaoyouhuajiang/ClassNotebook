//
// Created by Mila on 23.02.2020.
//

#ifndef UNTITLED_ARTILLERIST_H
#define UNTITLED_ARTILLERIST_H


#include "../Unit.h"

class Artillerist : public Unit{

protected:

    void whatYouName() override = 0;
    ObjectInterface* copy() override = 0;


};


#endif //UNTITLED_ARTILLERIST_H

