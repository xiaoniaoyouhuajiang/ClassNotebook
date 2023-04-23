#include "HumanCleric.h"


HumanCleric::HumanCleric(const HumanCleric& obj)
{
    this->hitPoint = obj.hitPoint;
    this->armor = obj.armor;
    this->damagePoint = obj.damagePoint;
    this->actionPoint = obj.actionPoint;
    this->character = obj.character;
    this->x_ = obj.x_;
    this->y_ = obj.y_;
}

//ВОзможно Удалить Копирование за ненадобностью

GameObj* HumanCleric::copy(GameField* field)
{
    HumanCleric* ret = new HumanCleric(*this);
    ret->setPosition(field, this->x_, this->y_);
    return ret;
}



void HumanCleric::initVariables(){
    hitPoint = HUMANCLERIC_HP;
    armor = HUMANCLERIC_ARM;
    actionPoint = ACTION_POINT;
    damagePoint = HUMANCLERIC_DM;
    character = HUMANCLERIC_VIEW;
 }


 HumanCleric::HumanCleric(GameField* field, int x, int y) : TMagicCharacter()
 {
    this->initVariables();
    this->setPosition(field, x, y);
 }
