#include "Healing.h"
#include "globalconst.h"



Healing::Healing(GameField* field, int x , int y)
 : healHp(HEAL_HP), life(true)
{
  character = HEALING_CHARACTER;
  setPosition(field, x, y);
}


void Healing::updateState(){

}


Healing::~Healing()
{

}
