//
// Created by olyaave on 31.05.2020.
//

#ifndef OOP_MAGE_H
#define OOP_MAGE_H

#include "Magician.h"

//  Mage - класс для магов.


class Mage : public Magician
{
public:
    Mage() : Magician(80, 200, 10,
            5, 10, 3, 'M'){}
};



#endif //OOP_MAGE_H
