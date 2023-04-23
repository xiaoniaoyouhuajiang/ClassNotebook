#include "ObjectFabric.h"


Crossbowman *ObjectFabric::createCrossbowman()
{
    auto newCrossbowman = new Crossbowman;
    return newCrossbowman;
}

Archer *ObjectFabric::createArcher()
{
    auto newArcher = new Archer;
    return newArcher;
}

Mage *ObjectFabric::createMage()
{
    auto newMage = new Mage;
    return newMage;
}

Witch *ObjectFabric::createWitch()
{
    auto newWitch = new Witch;
    return newWitch;
}

Knight *ObjectFabric::createKnight()
{
    auto newKnight = new Knight;
    return newKnight;
}

Spearman *ObjectFabric::createSpearman()
{
    auto newSpearman = new Spearman;
    return newSpearman;
}

Trap *ObjectFabric::createTrap()
{
    auto newTrap = new Trap;
    return newTrap;
}

AidKit *ObjectFabric::createAidKit()
{
    auto newAidKit = new AidKit;
    return newAidKit;
}

ShieldKit *ObjectFabric::createShieldKit()
{
    auto newShieldKit = new ShieldKit;
    return newShieldKit;
}

HolyTotem *ObjectFabric::createHolyTotem()
{
    auto newHolyTotem = new HolyTotem;
    return newHolyTotem;
}
