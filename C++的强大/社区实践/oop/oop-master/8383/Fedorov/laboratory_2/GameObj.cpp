#include "GameObj.h"
#include "Gamefield.h"


int GameObj::Count = 0;

GameObj::GameObj()
 : x_(0), y_(0), field_(nullptr), character('?')
{
  Count++;
}

bool GameObj::isHero()
{
    return false;
}

int GameObj::getAnimation()
{
    return  character;
}

bool GameObj::isNeutral()
{
    return false;
}


int GameObj::getSpace(){
   return 1;
}


int GameObj::getCount()
{
    return Count;
}


void GameObj::setPosition(GameField* field, int x, int y){
    this->field_ = field;
    this->x_ = x;
    this->y_ = y;
    field_->addObj(this);
}
