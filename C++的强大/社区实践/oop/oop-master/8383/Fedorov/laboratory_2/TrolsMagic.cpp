#include "TrolsMagic.h"


void TrolsMagic::initVariables() {
    hitPoint = TROLSMAGIC_HP;
    armor = TROLSMAGIC_ARM;
    actionPoint = ACTION_POINT;
    damagePoint = TROLSMAGIC_DM;
    character = TROLSMAGIC_VIEW;
}


TrolsMagic::TrolsMagic(GameField* field, int x, int y) : TMagicCharacter()
 {
    this->initVariables();
    this->setPosition(field, x, y);
 }


TrolsMagic::TrolsMagic(const TrolsMagic& obj)
{
    this->hitPoint = obj.hitPoint;
    this->armor = obj.armor;
    this->damagePoint = obj.damagePoint;
    this->actionPoint = obj.actionPoint;
    this->character = obj.character;
    this->x_ = obj.x_;
    this->y_ = obj.y_;
}



GameObj* TrolsMagic::copy(GameField* field)
{
    TrolsMagic* ret = new TrolsMagic(*this);
    ret->setPosition(field, this->x_, this->y_);
    return ret;
}
