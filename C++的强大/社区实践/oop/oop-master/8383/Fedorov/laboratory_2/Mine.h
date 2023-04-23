#ifndef MINE_H
#define MINE_H
#include "INeutralObj.h"


class Mine : public INeutralObj
{
  private:
    int damage;
    bool life;
  public:
    void updateState() override;
    Mine(GameField* field, int x, int y);
    friend Unit& operator+=(Unit& left, const Mine& right);
    virtual ~Mine();
};


#endif // MINE_H
