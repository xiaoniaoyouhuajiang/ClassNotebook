//
// Created by Artem Butko on 14/05/2020.
//

#ifndef OOP_NEW_MAGE_H
#define OOP_NEW_MAGE_H

#include "../Magician.h"

/*
 * Mage -- класс для магов.
 */

class Mage : public Magician
{
public:
    Mage() : Magician(80, 200, 10, 5, 10, 3, 'M'){}
};


#endif //OOP_NEW_MAGE_H
