#include "Mine.h"



Mine::Mine(GameField* field, int x , int y)
 : damage(MINE_DAMAGE), life(true)
{
  character = MINE_CHARACTER;
  setPosition(field, x, y);
}








void Mine::updateState(){

}



Mine::~Mine()
{

}
