#include "HumanTrebuchet.h"

void HumanTrebuchet::initVariables(){
   distantAttack = TREBUCHET_DISTANT;
   hitPoint = HUMANTREBUCHET_HP;
   armor = HUMANCLERIC_ARM;
   actionPoint = ACTION_POINT;
   damagePoint = HUMANTREBUCHET_DM;
   character = HUMANTREBUCHET_VIEW;
}


HumanTrebuchet::HumanTrebuchet(GameField* field, int x, int y) : TSiegeCharacter()
 {
    this->initVariables();
    this->setPosition(field, x, y);
 }

 HumanTrebuchet::HumanTrebuchet(const HumanTrebuchet& obj)
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



GameObj* HumanTrebuchet::copy(GameField* field)
{
    HumanTrebuchet* ret = new HumanTrebuchet(*this);
    ret->setPosition(field, this->x_, this->y_);
    return ret;
}
