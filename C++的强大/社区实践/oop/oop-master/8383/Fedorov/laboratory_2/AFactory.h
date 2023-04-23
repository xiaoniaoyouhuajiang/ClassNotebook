#ifndef AFACTORY_H
#define AFACTORY_H

//#include "TBattleCharacter.h"
#include "TMagicCharacter.h"
#include "TSiegeCharacter.h"


class AFactory{
  public:
   virtual TMagicCharacter* createTMagicCharacter(GameField* field, int x, int y) = 0;
   virtual TBattleCharacter * createTBattleCharacter(GameField* field, int x, int y) = 0;
   virtual TSiegeCharacter * createTSiegeCharacter(GameField* field, int x, int y) = 0;
   virtual ~AFactory() {}

};



#endif // AFACTORY_H
