#include "dynamicrangeunit.hpp"
using namespace unit;


DynamicRangeUnit::DynamicRangeUnit(const Position2D& position, std::shared_ptr<Mediator> mediator) :
    Unit(position, mediator)
{

}


DynamicRangeUnit::DynamicRangeUnit(const DynamicRangeUnit& unit) : Unit(unit),std::enable_shared_from_this<Unit>(unit)
{

}


bool DynamicRangeUnit::moveLeft()
{
    bool result = mediator->notify(shared_from_this(), MOVE_LEFT);

       if (result) {
           position.x--;
           return true;
       }

       return false;
}


bool DynamicRangeUnit::moveRight()
{
     bool result = mediator->notify(shared_from_this(), MOVE_RIGHT);

       if (result) {
           position.x++;
           return true;
       }
//
       return false;
}


bool DynamicRangeUnit::moveTop()
{
     bool result = mediator->notify(shared_from_this(), MOVE_TOP);

       if (result) {
           position.y--;
           return true;
       }

       return false;
}


bool DynamicRangeUnit::moveBottom()
{
    
    bool result = mediator->notify(shared_from_this(), MOVE_BOTTOM);

    if (result) {
        position.y++;
        return true;
    }

    return false;
}
