//
// Created by Artem Butko on 08/05/2020.
//

#ifndef OOP_NEW_CROSSBOWMAN_H
#define OOP_NEW_CROSSBOWMAN_H

#include "../Shooter.h"

/*
 * Crossbowman -- класс для стрелков-арбалетчиков.
 */

class Crossbowman : public Shooter
{
public:
    Crossbowman() : Shooter(100, 200, 15, 5, 30, 2, 'C'){};
};


#endif //OOP_NEW_CROSSBOWMAN_H
