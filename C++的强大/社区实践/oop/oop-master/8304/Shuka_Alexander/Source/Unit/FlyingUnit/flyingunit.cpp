#include "flyingunit.h"

using namespace unit;


FlyingUnit::FlyingUnit(const Point2D& point, std::shared_ptr<Mediator> mediator) :
    Unit(point, mediator)
{

}


FlyingUnit::FlyingUnit(const FlyingUnit& unit) : Unit(unit),
    std::enable_shared_from_this<Unit>(unit)
{

}


bool FlyingUnit::moveLeft()
{
    bool result = mediator->notify(shared_from_this(), MOVE_LEFT);

    if (result) {
        position.x--;
        return true;
    }

    return false;
}


bool FlyingUnit::moveRight()
{
    bool result = mediator->notify(shared_from_this(), MOVE_RIGHT);

    if (result) {
        position.x++;
        return true;
    }

    return false;
}


bool FlyingUnit::moveTop()
{
    bool result = mediator->notify(shared_from_this(), MOVE_TOP);

    if (result) {
        position.y--;
        return true;
    }

    return false;
}


bool FlyingUnit::moveBottom()
{
    bool result = mediator->notify(shared_from_this(), MOVE_BOTTOM);

    if (result) {
        position.y++;
        return true;
    }

    return false;
}


bool FlyingUnit::isFly() const
{
    return true;
}
