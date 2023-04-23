
#ifndef UNTITLED13_BLOCKBOWMAN_H
#define UNTITLED13_BLOCKBOWMAN_H

#include "Archer.h"
#include "../../../Armor/ChainArmor.h"

class BlockBowMan: public Archer{

public:

    BlockBowMan(): Archer(*ArmorFlyWeight::getFlyWeight<ChainArmor>(), 50){}

};

#endif //UNTITLED13_BLOCKBOWMAN_H
