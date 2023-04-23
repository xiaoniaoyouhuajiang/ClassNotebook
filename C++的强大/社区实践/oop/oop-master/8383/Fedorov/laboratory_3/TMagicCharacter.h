#ifndef TMAGICCHARACTER_H
#define TMAGICCHARACTER_H

#include "TBattleCharacter.h"

class TMagicCharacter : public TBattleCharacter{
  public:
      virtual void magicAttack() {}
      TMagicCharacter();
      virtual ~TMagicCharacter() {}
};


#endif // TMAGICCHARACTER_H
