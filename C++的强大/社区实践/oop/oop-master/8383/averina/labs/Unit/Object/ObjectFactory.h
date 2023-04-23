
#ifndef OOP_OBJECTFACTORY_H
#define OOP_OBJECTFACTORY_H

#include "../Types/Shooter/Crossbowman.h"
#include "../Types/Warrior/Knight.h"
#include "../Types/Warrior/Spearman.h"
#include "../Types/Shooter/Archer.h"
#include "../Types/Magician/Mage.h"
#include "../Types/Magician/Wizard.h"
#include "../NeutralObject/Object/AidKit.h"
#include "../NeutralObject/Object/Curse.h"
#include "../NeutralObject/Object/Potion.h"
#include "../NeutralObject/Object/Trap.h"

// абстрактная фабрика объектов

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

#endif //OOP_OBJECTFACTORY_H
