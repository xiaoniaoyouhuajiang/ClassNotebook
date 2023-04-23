#ifndef TERRAINPROXY_H
#define TERRAINPROXY_H
#include "globalconst.h"
#include "ITerrain.h"

class Terrain;

class TerrainProxy : public ITerrain
{
   protected:
      Terrain* realTerrain;
      int cellX, cellY;
   public:
      Obj getObj() override;
      void removeObj() override;
      Unit* getUnit() override;
      ///////
      //bool addObj(Obj) override {}
      ///////

      void affect() override {}
      int getAnimation() override;
      TerrainProxy(int x, int y);
      virtual ~TerrainProxy() {}
};

#endif // TERRAINPROXY_H
