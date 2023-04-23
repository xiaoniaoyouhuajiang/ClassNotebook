#ifndef HEALING_H
#define HEALING_H
#include "INeutralObj.h"


class Healing : public INeutralObj
{
  private:
    int healHp;
    bool life;
  public:
    void updateState() override;
    Healing(GameField* field, int x, int y);
    friend Unit& operator+=(Unit& left, const Healing& right);
    virtual ~Healing();
};

#endif // HEALING_H
