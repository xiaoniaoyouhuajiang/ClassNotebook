#ifndef OOP_CROSSBOWMAN_H
#define OOP_CROSSBOWMAN_H

#include "Shooter.h"

/*
 * Crossbowman -- класс для стрелков-арбалетчиков.
 */

class Crossbowman : public Shooter
{
public:
    Crossbowman() : Shooter(100, 200, 15, 5, 30, 2, 'C'){};
};


#endif //OOP_CROSSBOWMAN_H
