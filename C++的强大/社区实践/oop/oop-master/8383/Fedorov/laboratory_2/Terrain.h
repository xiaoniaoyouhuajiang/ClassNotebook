#ifndef TERRAIN_H
#define TERRAIN_H
#include "ITerrain.h"

class GameObj;
class TerrainTexture;

class AttributeTerrain
{
  protected:
    Obj obj = nullptr;
    TerrainTexture* texture;
    enum TerrainState {
        OPEN,
        CLOSED,
        /* ... */
    };
    TerrainState state;
  public:
    virtual ~AttributeTerrain();
};


class Terrain : public ITerrain, public AttributeTerrain
{
protected: 
    int cellX, cellY;
    void deleteObj();
public:
    virtual Obj getObj() override;
    virtual bool addObj(Obj obj_) override;
    virtual void removeObj() override;
    virtual void open() override;
    int getAnimation() override;
    virtual void setObj(Obj);
    Terrain(int, int);
    virtual ~Terrain();
};

#endif // TERRAIN_H
