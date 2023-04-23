//
// Created by mensch on 11.03.2020.
//

#ifndef OOP_LABS_KNIGHT_H
#define OOP_LABS_KNIGHT_H


#include "Swordsman.h"

class Knight : public Swordsman{

public:
    Knight();
    Texture texture() const override;
};


#endif //OOP_LABS_KNIGHT_H
