#include "Unit.h"
#include "Gamefield.h"
#include "Event.h"
#include "Mine.h"
#include "Portal.h"
#include "Healing.h"
#include "Armor.h"

Unit::Unit()
 : hitPoint(0), armor(0), actionPoint(0), damagePoint(0)
{
      Event event;
      event.type = Event::UNIT_CREATE;
      notify(this, event);
      character = '?';
      state_ = NORMAL;
}


void Unit::affectBlock()
{
   state_ = BLOCK_ATTACK;
}

void Unit::updateState()
{
  state_ = NORMAL;
}


bool Unit::move(int x, int y){
    updateState();
    return field_->move(this, x, y);
}



bool Unit::isDead()
{
    return hitPoint <= 0;
}

void Unit::loseHp(int hp)
{
    hitPoint -= hp;
}

void Unit::gainHp(int hp)
{
    hitPoint += hp;
}


bool Unit::isHero()
{
    return true;
}


void Unit::update()
{
  if (isDead())
    field_->deleteObj(this);
}


Unit::~Unit()
{
    Event event;
    event.type = Event::UNIT_DIE;
    notify(this, event);
}



Unit& operator+=(Unit& left, const Mine& right){
  left.hitPoint -= right.damage;
  //left.loseHP(right.damage)
  return left;
}


Unit& operator+=(Unit& left, const Healing& right){
  left.hitPoint += right.healHp;
  //left.gainHp(right.healHp);
  return left;
}


Unit& operator+=(Unit& left, const Portal& right){
  left.setPosition(left.field_, right.nextPlace->newX, right.nextPlace->newY);
  return left;
}



Unit& operator+=(Unit& left, const Armor& right){
  left.armor += right.armor;
  return left;
}
