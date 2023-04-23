#include "TerrainProxy.h"
#include "Terrain.h"


TerrainProxy::TerrainProxy(int x, int y)
 : realTerrain(nullptr),cellX(x), cellY(y) {}



void TerrainProxy::removeObj()
{
  if (realTerrain != nullptr){
     realTerrain->removeObj();
  }
}


Obj TerrainProxy::getObj()
{
   if (realTerrain == nullptr){
      return nullptr;
   }
   return realTerrain->getObj();
}



int TerrainProxy::getAnimation(){
    if (realTerrain){
        return realTerrain->getAnimation();
    }
    return 0;
}
