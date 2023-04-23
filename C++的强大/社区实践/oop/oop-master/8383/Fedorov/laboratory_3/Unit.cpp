#include "Unit.h"
#include "Gamefield.h"
#include "Event.h"
#include "Mine.h"
#include "Portal.h"
#include "Healing.h"
#include "Armor.h"
#include "Mediator.h"

Unit::Unit()
 : hitPoint(0), armor(0), actionPoint(0), damagePoint(0), relation(Event::FRIEND), attackMediator(nullptr)
{
      Event event;
      event.type = Event::UNIT_CREATE;
      notify(this, event);
      character = '?';
      state_ = Event::HeroState::NORMAL;
}


void Unit::affectBlock()
{
   state_ = Event::HeroState::BLOCK_ATTACK;
}

void Unit::updateState()
{
  state_ = Event::HeroState::NORMAL;
}


bool Unit::move(int x, int y){
    updateState();
    return field_->move(this, x, y);
}


void Unit::setMediator(IMediator *mediator){
    if(attackMediator==nullptr)
        attackMediator = mediator;
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


Event::Relation Unit::getRelation(){
    return relation;
}


Event Unit::getInfo(){
    Event event;
    event.type = Event::UNIT_INFO;
    event.unitInfo.hitPoint = hitPoint;
    event.unitInfo.damagePoint = damagePoint;
    event.unitInfo.armor = armor;
    event.unitInfo.state_ = state_;
    event.unitInfo.relation = relation;
    event.unitInfo.unitType = type;
    event.unitInfo.actionPoint = actionPoint;
    event.unitInfo.rase = race;
    event.unitInfo.distantAttack = distantAttack;
    return event;
}


Unit::~Unit()
{
    Event event;
    event.type = Event::UNIT_DIE;
    notify(this, event);
}

bool Unit::attack(int x, int y) {
    if (attackMediator)
        return attackMediator->notify(this, x, y);
    return false;
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


Event Unit::getAttackAttribute(){

}
