//
// Created by Artem Butko on 08/05/2020.
//

#ifndef OOP_NEW_ARCHER_H
#define OOP_NEW_ARCHER_H

#include "../Shooter.h"

/*
 * Archer -- класс для стрелков-лучников.
 */

class Archer : public Shooter
{
public:
    Archer() : Shooter(80, 200, 10, 5, 10, 3, 'A'){}
};


#endif //OOP_NEW_ARCHER_H
