//
// Created by mensch on 02.03.2020.
//

#ifndef OOP_LABS_CROSSBOWMAN_H
#define OOP_LABS_CROSSBOWMAN_H


#include "Archer.h"

class Crossbowman : public Archer{

public:
    Crossbowman();
    Texture texture() const override;
};


#endif //OOP_LABS_CROSSBOWMAN_H
