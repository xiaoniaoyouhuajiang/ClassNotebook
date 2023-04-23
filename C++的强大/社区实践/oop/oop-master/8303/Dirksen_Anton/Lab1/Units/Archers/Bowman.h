//
// Created by mensch on 02.03.2020.
//

#ifndef OOP_LABS_BOWMAN_H
#define OOP_LABS_BOWMAN_H


#include "Archer.h"

class Bowman : public Archer {

public:
    Bowman();
    Texture texture() const override;
};


#endif //OOP_LABS_BOWMAN_H
