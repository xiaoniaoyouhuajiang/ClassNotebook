#ifndef TSIEGECHARACTER_H
#define TSIEGECHARACTER_H

#include "Unit.h"


class TSiegeCharacter: public Unit {
  protected:
    int distantAttack;
  public:
    virtual void shoot() {}
    TSiegeCharacter();
    virtual ~TSiegeCharacter() {}
};



#endif // TSIEGECHARACTER_H


