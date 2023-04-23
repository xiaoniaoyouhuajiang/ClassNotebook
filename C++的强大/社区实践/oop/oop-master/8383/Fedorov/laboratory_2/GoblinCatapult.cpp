#include "GoblinCatapult.h"

void GoblinCatapult::initVariables()
{
   distantAttack = CATAPULT_DISTANT;
   hitPoint = GOBLINCATAPULT_HP;
   armor = GOBLINCATAPULT_ARM;
   actionPoint = ACTION_POINT;
   damagePoint = GOBLINCATAPULT_DM;
   character = GOBLINCATAPULT_VIEW;
}

 GoblinCatapult::GoblinCatapult(GameField* field, int x, int y)
  : TSiegeCharacter(), fireBall(0)
 {
    this->initVariables();
    this->setPosition(field, x, y);
 }




  GoblinCatapult::GoblinCatapult(const GoblinCatapult& obj)
{
    this->hitPoint = obj.hitPoint;
    this->armor = obj.armor;
    this->damagePoint = obj.damagePoint;
    this->actionPoint = obj.actionPoint;
    this->character = obj.character;
    this->distantAttack = obj.distantAttack;
    this->x_ = obj.x_;
    this->y_ = obj.y_;
}



GameObj* GoblinCatapult::copy(GameField* field)
{
    GoblinCatapult* ret = new GoblinCatapult(*this);
    ret->setPosition(field, this->x_, this->y_);
    return ret;
}
