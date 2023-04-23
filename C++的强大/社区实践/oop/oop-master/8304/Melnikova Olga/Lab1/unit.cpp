#include "unit.h"
#include "object.h"
#include "cmath"

Unit::Unit()
{
    damage = 0;
    movementRadius = 0;
    attackRadius = 0;
}

bool Unit::canMove(int x, int y) {
    if (Object::canMove(x,y)) {
        int l = abs(x - this->x) + abs(y - this->y);
        if (l <= this->movementRadius) return true;
    }
    return false;
}
