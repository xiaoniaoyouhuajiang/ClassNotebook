#ifndef GRASS_H
#define GRASS_H

#include "Terrain.h"
class GrassTexture;

class Grass : public Terrain
{
public:
    bool isMovement() override;
    int getMovementCost() override;
    void affect() override {}       //у травы никакого влияния
    Grass(int,int, bool open_ = false);
    virtual ~Grass() {}
};

#endif // GRASS_H
