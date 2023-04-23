#include "ChaosFactory.h"
#include "Gretchin.h"
#include "TrolsMagic.h"
#include "GoblinCatapult.h"



 TMagicCharacter* ChaosFactory::createTMagicCharacter(GameField* field, int x, int y){
    return new TrolsMagic(field,x, y);
  }

 TBattleCharacter* ChaosFactory::createTBattleCharacter(GameField* field, int x, int y) {
    return new Gretchin(field,x, y);
 }

 TSiegeCharacter* ChaosFactory::createTSiegeCharacter(GameField* field, int x, int y){
    return new GoblinCatapult(field,x, y);
 }
