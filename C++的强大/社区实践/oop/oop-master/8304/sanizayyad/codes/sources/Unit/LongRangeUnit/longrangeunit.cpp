#include "longrangeunit.hpp"

using namespace unit;


LongRangeUnit::LongRangeUnit(const Position2D& position, std::shared_ptr<Mediator> mediator) :
    Unit(position, mediator)
{

}


LongRangeUnit::LongRangeUnit(const LongRangeUnit& unit) : Unit(unit),std::enable_shared_from_this<Unit>(unit)
{

}


bool LongRangeUnit::moveLeft()
{
    bool result = mediator->notify(shared_from_this(), MOVE_LEFT);

       if (result) {
           position.x--;
           return true;
       }
       return false;
}


bool LongRangeUnit::moveRight()
{
     bool result = mediator->notify(shared_from_this(), MOVE_RIGHT);

       if (result) {
           position.x++;
           return true;
       }
       return false;
}


bool LongRangeUnit::moveTop()
{
     bool result = mediator->notify(shared_from_this(), MOVE_TOP);

       if (result) {
           position.y--;
           return true;
       }

       return false;
}


bool LongRangeUnit::moveBottom()
{
    
    bool result = mediator->notify(shared_from_this(), MOVE_BOTTOM);

    if (result) {
        position.y++;
        return true;
    }

    return false;
}

