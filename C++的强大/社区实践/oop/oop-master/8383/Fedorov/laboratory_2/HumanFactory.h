#ifndef HUMANFACTORY_H
#define HUMANFACTORY_H

#include "AFactory.h"

//class GameField;

class HumanFactory: public AFactory{
 public:
  TMagicCharacter* createTMagicCharacter(GameField* field, int x, int y) override;

  TBattleCharacter* createTBattleCharacter(GameField* field, int x, int y) override;

  TSiegeCharacter* createTSiegeCharacter(GameField* field, int x, int y) override;
};

#endif // HUMANFACTORY_H
