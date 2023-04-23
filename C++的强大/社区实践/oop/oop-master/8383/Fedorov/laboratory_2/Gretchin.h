#ifndef GRETCHIN_H
#define GRETCHIN_H

#include "TBattleCharacter.h"


class Gretchin : public TBattleCharacter{
  private:
    int comradeCount;
    void initVariables();
  public:
    Gretchin(const Gretchin& obj);
    GameObj* copy(GameField* field);
    Gretchin(GameField* field, int x, int y);
    void attack() override {}
    /* атака с бонусом от рядом находящихся */
    virtual ~Gretchin() {}
};

#endif // GRETCHIN_H
