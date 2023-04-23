#include "GrassProxy.h"
#include "Grass.h"


bool GrassProxy::addObj(Obj obj_)
{
   if (realTerrain == nullptr){
     realTerrain = new Grass(cellX, cellY);
   }

   return realTerrain->addObj(obj_);
}


GrassProxy::~GrassProxy()
{
    if (realTerrain != nullptr){
        delete realTerrain;
    }
}


GrassProxy::GrassProxy(int x, int y, bool open_)
 : TerrainProxy(x,y)
{
    realTerrain = nullptr;
    if (open_ == true){
        realTerrain = new Grass(cellX, cellY);
        realTerrain->open();
    }
}



int GrassProxy::getMovementCost()
{
    return GRASS_COST;
}

bool GrassProxy::isMovement()
{
    if (realTerrain == nullptr){
        return GRASS_MOVEABLE;
    }

    else{
        return realTerrain->isMovement();
    }
}


void GrassProxy::open()
{
    if (realTerrain == nullptr){
        realTerrain = new Grass(cellX, cellY);
    }
    realTerrain->open();
}
