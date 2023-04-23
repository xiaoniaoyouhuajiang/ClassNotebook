#ifndef OOP_LAB1_ARCHERFACTORY_H
#define OOP_LAB1_ARCHERFACTORY_H

#include "UnitFactory.h"
#include "../Unit/Archer/Sniper.h"
#include "../Unit/Archer/CrossBowMan.h"

class ArcherFactory : UnitFactory {
 public:
  CrossBowMan *createFirst() {
    return new CrossBowMan;
  }
  Sniper *createSecond() {
    return new Sniper();
  }
};

#endif //OOP_LAB1_ARCHERFACTORY_H