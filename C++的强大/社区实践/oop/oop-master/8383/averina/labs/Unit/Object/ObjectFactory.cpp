
#include "ObjectFactory.h"


Mage *ObjectFactory::createMage()
{
    return new Mage;
}

Wizard *ObjectFactory::createWizard()
{
    return new Wizard;
}

Archer *ObjectFactory::createArcher()
{
    return new Archer;
}

Crossbowman *ObjectFactory::createCrossbowman()
{
    return new Crossbowman;
}

Knight *ObjectFactory::createKnight()
{
    return new Knight;
}

Spearman *ObjectFactory::createSpearman()
{
    return new Spearman;
}

AidKit *ObjectFactory::createAidKit()
{
    return new AidKit;
}

Curse *ObjectFactory::createCurse()
{
    return new Curse;
}

Potion *ObjectFactory::createPotion()
{
    return new Potion;
}

Trap *ObjectFactory::createTrap()
{
    return new Trap;
}