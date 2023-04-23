#ifndef STONE_H
#define STONE_H

#include "Terrain.h"
class StoneTexture;

class Stone : public Terrain
{
public:
    Obj getObj() override;
    bool addObj(Obj) override;
    bool isMovement() override;
    int getMovementCost() override;
    void affect() override;
    Stone(int,int);
    //virtual ~Grass();
};

#endif // STONE_H
