#include "UnitFactory.h"

Unit *Tier1Factory::createType1() {
    return new Swordsman;
}

Unit *Tier1Factory::createType2() {
    return new Shieldman;
}

Unit *Tier2Factory::createType1() {
    return new NoviceArcher;
}

Unit *Tier2Factory::createType2() {
    return new MasterArcher;
}

Unit *Tier3Factory::createType1() {
    return new Paladin;
}

Unit *Tier3Factory::createType2() {
    return new Cavalier;
}