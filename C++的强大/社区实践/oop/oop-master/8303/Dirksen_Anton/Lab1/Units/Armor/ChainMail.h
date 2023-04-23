//
// Created by mensch on 4/4/20.
//

#include "Armor.h"

#ifndef OOP_LABS_CHAINMAIL_H
#define OOP_LABS_CHAINMAIL_H

#endif //OOP_LABS_CHAINMAIL_H

class ChainMail : public Armor{
public:
    ChainMail(){
        physicDamageReduction = 17;
        magicDamageReduction = 5;
        weight = 10.5;
    }

};