#include "BaseConstructor.h"
#include "ChaosBase.h"
#include "HumanBase.h"
#include "Gamefield.h"

BaseConstructor::BaseConstructor(GameField* field)
: field_(field) {}


Base* BaseConstructor::createHumanBase(int x, int y)
{
  if (!isMovementBase(x,y)) return nullptr;
  return new HumanBase(field_, x, y);
}


Base* BaseConstructor::createChaosBase(int x, int y)
{
  if (!isMovementBase(x,y)) return nullptr;
  return new ChaosBase(field_, x, y);
}



bool BaseConstructor::isMovementBase(int x, int y)
{
  if (x<0 || y<0 || x>field_->getHeight()-1 || y>field_->getWidth()-1)
      return false;
  if (field_->gridView[x][y] == 1)
      return true;
  return false;
}




BaseConstructor::~BaseConstructor()
{

}
