#include "Grass.h"
#include "GameObj.h"
#include "GrassTexture.h"

bool Grass::isMovement()
{
  /* STATE ВЛИЯЕТ */
    if (obj && obj->isNeutral()) return true;
    if (obj == nullptr) return true;
    return false;
}


int Grass::getMovementCost()
{
  return GRASS_COST;
}



Grass::Grass(int x, int y, bool open_) //: movementCost(GRASS_COST),  moveable(GRASS_MOVEABLE),
 : Terrain(x, y)
{
    if (texture == nullptr){
        texture = new GrassTexture;
    }
    this->obj = nullptr;
    this->state = CLOSED;
    if (open_){
        open();
    }
}

