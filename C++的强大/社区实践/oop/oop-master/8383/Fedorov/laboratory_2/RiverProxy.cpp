#include "RiverProxy.h"
#include "River.h"


bool RiverProxy::addObj(Obj obj_)
{
   if (realTerrain == nullptr){
     realTerrain = new River(cellX, cellY);
   }

   return realTerrain->addObj(obj_);
}



RiverProxy::~RiverProxy()
{
    if (realTerrain != nullptr){
        delete realTerrain;
    }
}


RiverProxy::RiverProxy(int x, int y, bool open_)
 : TerrainProxy(x,y)
{
    realTerrain = nullptr;
    if (open_ == true){
        realTerrain = new River(cellX, cellY);
        realTerrain->open();
    }
}



int RiverProxy::getMovementCost()
{
    return RIVER_COST;
}

bool RiverProxy::isMovement()
{
    if (realTerrain == nullptr){
        return RIVER_MOVEABLE;
    }

    else{
        return realTerrain->isMovement();
    }
}


void RiverProxy::open()
{
    if (realTerrain == nullptr){
        realTerrain = new River(cellX, cellY);
    }
    realTerrain->open();
}

