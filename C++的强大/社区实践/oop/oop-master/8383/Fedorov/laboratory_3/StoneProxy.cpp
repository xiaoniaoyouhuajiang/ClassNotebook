#include "StoneProxy.h"
#include "Stone.h"

bool StoneProxy::addObj(Obj obj_)
{
   if (realTerrain == nullptr){
     realTerrain = new Stone(cellX, cellY);
   }
   //// Можно убрать и оставить просто return false;
   return realTerrain->addObj(obj_);
}

Obj StoneProxy::getObj()
{
    return nullptr;
}


StoneProxy::~StoneProxy()
{
    if (realTerrain != nullptr){
        delete realTerrain;
    }
}

StoneProxy::StoneProxy(int x, int y, bool open_)
 : TerrainProxy(x,y)
{
    realTerrain = nullptr;
    if (open_ == true){
        realTerrain = new Stone(cellX, cellY);
        realTerrain->open();
    }
}



int StoneProxy::getMovementCost()
{
    return ROCK_COST;
}

bool StoneProxy::isMovement()
{
    if (realTerrain == nullptr){
        return ROCK_MOVEABLE;
    }

    else{
        return realTerrain->isMovement();
    }
}


void StoneProxy::open()
{
    if (realTerrain == nullptr){
        realTerrain = new Stone(cellX, cellY);
    }
    realTerrain->open();
}
