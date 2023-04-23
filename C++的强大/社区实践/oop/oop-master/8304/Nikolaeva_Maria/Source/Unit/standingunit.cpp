#include "standingunit.h"


bool StandingUnit::move(int dx, int dy)
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


bool StandingUnit::isFlying()
{
    return false;
}
