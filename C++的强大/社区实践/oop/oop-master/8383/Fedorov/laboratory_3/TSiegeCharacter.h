#ifndef TSIEGECHARACTER_H
#define TSIEGECHARACTER_H

//#include "Unit.h"
#include "TBattleCharacter.h"

class TSiegeCharacter: public TBattleCharacter {
  public:
    virtual void shoot() {}
    TSiegeCharacter();
    virtual ~TSiegeCharacter() {}
};



#endif // TSIEGECHARACTER_H


