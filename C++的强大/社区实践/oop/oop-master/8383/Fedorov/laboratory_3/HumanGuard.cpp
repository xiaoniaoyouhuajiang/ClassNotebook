#include "HumanGuard.h"

void HumanGuard::initVariables(){
   hitPoint = HUMANGUARD_HP;
   armor = HUMANCLERIC_ARM;
   actionPoint = ACTION_POINT;
   damagePoint = HUMANGUARD_DM;
   character = HUMANGUARD_VIEW;
}


HumanGuard::HumanGuard(GameField* field, int x, int y)
 : TBattleCharacter(), moralityPoint(0)
 {
    this->initVariables();
    this->setPosition(field, x, y);
 }

HumanGuard::HumanGuard(const HumanGuard& obj)
{
    this->hitPoint = obj.hitPoint;
    this->armor = obj.armor;
    this->damagePoint = obj.damagePoint;
    this->actionPoint = obj.actionPoint;
    this->character = obj.character;
    this->moralityPoint = obj.moralityPoint;
    this->x_ = obj.x_;
    this->y_ = obj.y_;
}



GameObj* HumanGuard::copy(GameField* field)
{
    HumanGuard* ret = new HumanGuard(*this);
    ret->setPosition(field, this->x_, this->y_);
    return ret;
}
