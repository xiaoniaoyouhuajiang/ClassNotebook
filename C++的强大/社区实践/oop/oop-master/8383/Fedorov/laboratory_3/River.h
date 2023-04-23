#ifndef RIVER_H
#define RIVER_H

#include "Terrain.h"
class RiverTexture;

class River : public Terrain
{
public:
    bool isMovement() override;
    int getMovementCost() override;
    void affect() override;
    bool addObj(Obj) override;
    River(int,int);
    //virtual ~Grass();
};

#endif // RIVER_H
