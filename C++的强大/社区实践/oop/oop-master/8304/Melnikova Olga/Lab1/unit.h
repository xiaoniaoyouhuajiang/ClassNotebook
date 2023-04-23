#pragma once
#include "object.h"
#include "cell.h"

constexpr int LIGHT_RADIUS = 1;
constexpr int MEDIUM_RADIUS = 2;
constexpr int HEAVY_RADIUS = 3;
constexpr int DAMAGE = 1;

class Unit : public Object
{
public:
    Unit();
    //~Unit();
    int damage;
    int movementRadius;
    int attackRadius;

    bool canMove(int x, int y);
};
