//
// Created by Artem Butko on 14/05/2020.
//

#ifndef OOP_NEW_OBJECTFACTORY_H
#define OOP_NEW_OBJECTFACTORY_H

#include "../../Objects/Units/Shooters/Crossbowman/Crossbowman.h"
#include "../../Objects/Units/Warriors/Spearman/Spearman.h"
#include "../../Objects/Units/Warriors/Knight/Knight.h"
#include "../../Objects/Units/Shooters/Archer/Archer.h"
#include "../../Objects/Units/Magicians/Wizard/Wizard.h"
#include "../../Objects/Units/Magicians/Mage/Mage.h"
#include "../../Objects/Neutral/AidKit/AidKit.h"
#include "../../Objects/Neutral/Curse/Curse.h"
#include "../../Objects/Neutral/Potion/Potion.h"
#include "../../Objects/Neutral/Trap/Trap.h"

/*
 * ObjectFactory -- абстрактная фабрика объектов.
 */

class ObjectFactory
{
public:
    Mage* createMage();
    Wizard* createWizard();
    Archer* createArcher();
    Crossbowman* createCrossbowman();
    Knight* createKnight();
    Spearman* createSpearman();
    AidKit* createAidKit();
    Curse* createCurse();
    Potion* createPotion();
    Trap* createTrap();
};


#endif //OOP_NEW_OBJECTFACTORY_H
