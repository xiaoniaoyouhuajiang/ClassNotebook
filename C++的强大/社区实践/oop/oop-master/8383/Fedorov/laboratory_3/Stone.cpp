#include "Stone.h"
#include "StoneTexture.h"

Obj Stone::getObj()
{
  return nullptr;
}


bool Stone::addObj(Obj obj_)
{
  return false;
}


bool Stone::isMovement()
{
    return false;
}


int Stone::getMovementCost()
{
    ///return movementCost;
  return ROCK_COST;
}

Stone::Stone(int x, int y)
 : Terrain(x,y)
{
    if (texture == nullptr){
        texture = new StoneTexture;
    }
    this->obj = nullptr;
    this->state = CLOSED;
}

void Stone::affect() {}
