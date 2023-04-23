#ifndef NEW_LR1_OBJECTFABRIC_H
#define NEW_LR1_OBJECTFABRIC_H

#include "Unit/Archer/Crossbowman/Crossbowman.h"
#include "Unit/Archer/Archer/Archer.h"
#include "Unit/Mage/Mage/Mage.h"
#include "Unit/Mage/Witch/Witch.h"
#include "Unit/Warrior/Knight/Knight.h"
#include "Unit/Warrior/Spearman/Spearman.h"
#include "Neutral/Trap/Trap.h"
#include "Neutral/AidKit/AidKit.h"
#include "Neutral/ShieldKit/ShieldKit.h"
#include "Neutral/HolyTotem/HolyTotem.h"


class ObjectFabric
{
public:
    Crossbowman* createCrossbowman();
    Archer* createArcher();
    Mage* createMage();
    Witch* createWitch();
    Knight* createKnight();
    Spearman* createSpearman();
    Trap* createTrap();
    AidKit* createAidKit();
    ShieldKit* createShieldKit();
    HolyTotem* createHolyTotem();
};


#endif //NEW_LR1_OBJECTFABRIC_H
