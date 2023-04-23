#ifndef OOP_WIZARD_H
#define OOP_WIZARD_H

#include "Magician.h"
/*
 * Wizard -- класс для волшебников.
 */

class Wizard : public Magician
{
public:
    Wizard() : Magician(150, 250, 35,
            3, 20, 1, 'W'){}
};


#endif //OOP_WIZARD_H
