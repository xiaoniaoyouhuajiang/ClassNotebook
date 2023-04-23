#ifndef UNIT_H
#define UNIT_H

#include "GameObj.h"
class Mine;
class Healing;
class Portal;
class Armor;

class IUnit
{
public:
    virtual bool move(int x, int y) = 0;
    virtual void affectBlock() = 0;
    virtual bool isDead() = 0;
    virtual void loseHp(int) = 0;
    virtual void gainHp(int) = 0;

};


class Unit : public GameObj, public IUnit
{
private:
    friend Unit& operator+=(Unit& left, const Mine& right);
    friend Unit& operator+=(Unit& left, const Healing& right);
    friend Unit& operator+=(Unit& left, const Portal& right);
    friend Unit& operator+=(Unit& left, const Armor& right);
public:
    enum HeroState{  BLOCK_ATTACK, BLOCK_MOVEABLE, NORMAL
       /* ... */
    };
protected:
  int hitPoint;
  int armor;
  int actionPoint;
  int damagePoint;
  HeroState state_;
public:
  virtual bool move(int x, int y) override;
  virtual void update() override;                          /* Исправить потом */
  bool isDead() override;
  void loseHp(int hp) override;
  void gainHp(int hp) override;
  bool isHero() override;
  void affectBlock() override;
  void updateState();
  Unit();
  virtual ~Unit();
};

#endif // UNIT_H
