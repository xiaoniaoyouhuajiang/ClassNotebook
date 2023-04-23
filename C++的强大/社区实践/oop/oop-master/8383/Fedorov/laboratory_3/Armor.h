#ifndef ARMOR_H
#define ARMOR_H


#include "INeutralObj.h"

class Armor : public INeutralObj
{
  private:
    int armor;
    bool life;
  public:
    void updateState() override;
    Armor(GameField* field, int x, int y);
    friend Unit& operator+=(Unit& left, const Armor& right);
    virtual ~Armor();
};

#endif // ARMOR_H
