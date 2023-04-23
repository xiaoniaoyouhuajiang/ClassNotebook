
#ifndef OOP_KNIGHT_H
#define OOP_KNIGHT_H

#include "Warrior.h"

//  Knight -- класс для войнов-рыцарей.

class Knight : public Warrior
{ ;
public:
    Knight() : Warrior(200, 100, 25,
            1, 20, 2, 'K'){}
};

#endif //OOP_KNIGHT_H
