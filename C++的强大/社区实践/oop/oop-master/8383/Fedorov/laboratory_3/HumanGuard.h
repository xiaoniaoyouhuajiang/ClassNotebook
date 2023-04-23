#ifndef HUMANGUARD_H
#define HUMANGUARD_H

#include "TBattleCharacter.h"

class HumanGuard : public TBattleCharacter {
  private:
    void initVariables();
    int moralityPoint;
  public:
    HumanGuard(const HumanGuard& obj);
    GameObj* copy(GameField* field);
    HumanGuard(GameField* field, int x, int y);
    /*атакa с бонусом от морали */
    virtual ~HumanGuard() {}
};


#endif // HUMANGUARD_H
