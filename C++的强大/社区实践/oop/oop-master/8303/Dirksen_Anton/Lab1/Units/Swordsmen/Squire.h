//
// Created by mensch on 11.03.2020.
//

#ifndef OOP_LABS_SQUIRE_H
#define OOP_LABS_SQUIRE_H


#include "Swordsman.h"

class Squire : public Swordsman{
public:
    Squire();
    Texture texture() const override;
};


#endif //OOP_LABS_SQUIRE_H
