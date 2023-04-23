#include "HumanFactory.h"


#include "HumanCleric.h"
#include "HumanGuard.h"
#include "HumanTrebuchet.h"


TMagicCharacter* HumanFactory::createTMagicCharacter(GameField* field, int x, int y) {
  return new HumanCleric(field,x, y);
}

TBattleCharacter* HumanFactory::createTBattleCharacter(GameField* field, int x, int y)  {
  return new HumanGuard(field,x, y);
}

TSiegeCharacter* HumanFactory::createTSiegeCharacter(GameField* field, int x, int y) {
  return new HumanTrebuchet(field,x, y);
}
