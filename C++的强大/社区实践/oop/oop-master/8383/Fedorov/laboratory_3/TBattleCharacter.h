#ifndef TBATTLECHARACTER_H
#define TBATTLECHARACTER_H
#include "Unit.h"

class TBattleCharacter : public Unit {
  public:
      virtual Event getAttackAttribute() override;
      TBattleCharacter();
      virtual ~TBattleCharacter() {}
};


#endif // TBATTLECHARACTER_H
