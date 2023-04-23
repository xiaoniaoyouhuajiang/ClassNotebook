#include "infantryunit.h"


bool InfantryUnit::move(int dx, int dy)
{
    int x = this->coordinate->x;
    int y = this->coordinate->y;

    if (this->mediator->notify(this, x + dx, y + dy)) {
        this->coordinate->x += dx;
        this->coordinate->y += dy;

        return true;
    }

    return false;
}


bool InfantryUnit::isFlying()
{
    return false;
}
