
#ifndef UnitsFactory_h
#define UnitsFactory_h

#include <stdio.h>
#include "Units.h"

class UnitsFactory{
public:
    virtual Rogue* createRogue() = 0;
    virtual Mage* createMage() = 0;
    virtual Warrior* createWarrior() = 0;
};

class MagicallyResilientFactory: public UnitsFactory{
public:
    Rogue* createRogue() override{
        return new Ranger;
    }

    Mage* createMage() override{
        return new Witch;
    }

    Warrior* createWarrior() override{
        return new LanceKnight;
    }
};

class PhysicallyResilientFactory: public UnitsFactory{
public:
    Rogue* createRogue() override{
      return new Slayer;
    }

    Mage* createMage() override{
      return new BattleMage;
    }

    Warrior* createWarrior() override{
      return new Paladin;
    }
    
};
#endif /* UnitsFactory_h */
