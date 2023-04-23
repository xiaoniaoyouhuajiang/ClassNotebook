#include "Gretchin.h"

void Gretchin::initVariables(){
    hitPoint = GRETCHIN_HP;
    armor = GRETCHIN_ARM;
    actionPoint = ACTION_POINT;
    damagePoint = GRETCHIN_DM;
    character = GRETCHIN_VIEW;
}


Gretchin::Gretchin(GameField* field, int x, int y)
  : TBattleCharacter(), comradeCount(0)
{
    this->initVariables();
    this->setPosition(field, x, y);
}


// Удалить конструкторы копирования
// И метод создания копии
Gretchin::Gretchin(const Gretchin& obj)
{
    this->hitPoint = obj.hitPoint;
    this->armor = obj.armor;
    this->damagePoint = obj.damagePoint;
    this->actionPoint = obj.actionPoint;
    this->character = obj.character;
    this->comradeCount = obj.comradeCount;
    this->x_ = obj.x_;
    this->y_ = obj.y_;
}



GameObj* Gretchin::copy(GameField* field)
{
    Gretchin* ret = new Gretchin(*this);
    ret->setPosition(field, this->x_, this->y_);
    return ret;
}
