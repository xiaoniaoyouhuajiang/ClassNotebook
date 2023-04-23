//
// Created by Artem Butko on 14/05/2020.
//

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

