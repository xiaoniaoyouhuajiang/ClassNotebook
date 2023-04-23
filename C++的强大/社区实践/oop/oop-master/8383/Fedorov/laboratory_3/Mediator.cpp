#include "Mediator.h"
#include "Gamefield.h"
#include "Unit.h"
#include "Base.h"
#include <cmath>

int AttackMediator::getDistant(int x1, int y1, int x2, int y2){
    int distant = static_cast<int>(sqrt(static_cast<float>(pow((x2-x1),2)+pow((y2-y1),2))));
    return distant;
}


bool AttackMediator::notify(Unit *attacker, int x, int y){
    if (x<0||y<0||x>field->getHeight()-1 || y>field->getWidth()-1)
        return false;
    int distant = getDistant(attacker->getX(), attacker->getY(), x, y);
    Obj obj = field->getObj(x,y);
    Event attribute = attacker->getAttackAttribute();
    if (obj && attribute.type==Event::ATTACK_ATTRIBUTE){
          if (distant > attribute.attackAttribute.distant){
              return false;
          }
          else if(obj->isHero()){
              Unit* unit = (Unit*)obj;
              if (attacker->getRelation() == unit->getRelation())
                  return false;
              unit->loseHp(attribute.attackAttribute.damage+attribute.attackAttribute.bonus);
              if(unit->isDead()) field->deleteObj(x,y);
              return true;
          }
          else if(typeid(*obj)==typeid(Base)){
              Base* base = (Base*)obj;
              if (attacker->getRelation()==base->getRelation())
                  return false;
              base->loseHp(attribute.attackAttribute.bonus+attribute.attackAttribute.damage);
              if(base->isDead()) field->deleteObj(x,y);
              return true;
          }

     }
    return false;
}

AttackMediator::AttackMediator(GameField* field)
    :field(field)
{
}

AttackMediator::~AttackMediator(){

}


IMediator::~IMediator()
{}
