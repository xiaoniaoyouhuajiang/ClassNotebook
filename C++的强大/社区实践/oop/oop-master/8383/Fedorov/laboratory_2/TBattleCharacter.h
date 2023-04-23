#ifndef TBATTLECHARACTER_H
#define TBATTLECHARACTER_H
#include "Unit.h"

class TBattleCharacter : public Unit {
  public:
      virtual void attack() {}
      TBattleCharacter();
      virtual ~TBattleCharacter() {}
};


#endif // TBATTLECHARACTER_H
