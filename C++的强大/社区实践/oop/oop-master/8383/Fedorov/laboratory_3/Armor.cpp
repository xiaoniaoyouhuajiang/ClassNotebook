#include "Armor.h"


Armor::Armor(GameField* field, int x , int y)
 : armor(ARMOR_NEUTRAL), life(true)
{
  character = ARMOR_CHARACTER;
  setPosition(field, x, y);
}

void Armor::updateState(){

}

Armor::~Armor()
{

}

