#ifndef CHAOSFACTORY_H
#define CHAOSFACTORY_H

#include "AFactory.h"

class ChaosFactory: public AFactory{
  public:
    TMagicCharacter* createTMagicCharacter(GameField* field, int x, int y) override;

    TBattleCharacter* createTBattleCharacter(GameField* field, int x, int y) override;

    TSiegeCharacter* createTSiegeCharacter(GameField* field, int x, int y) override;
};
#endif // CHAOSFACTORY_H
