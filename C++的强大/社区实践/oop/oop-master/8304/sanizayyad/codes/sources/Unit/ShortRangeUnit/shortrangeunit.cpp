#include "shortRangeUnit.hpp"

using namespace unit;


ShortRangeUnit::ShortRangeUnit(const Position2D& position, std::shared_ptr<Mediator> mediator) :
    Unit(position, mediator)
{

}

ShortRangeUnit::ShortRangeUnit(const ShortRangeUnit& unit) : Unit(unit),std::enable_shared_from_this<Unit>(unit)
{

}


bool ShortRangeUnit::moveLeft()
{
    bool result = mediator->notify(shared_from_this(), MOVE_LEFT);

       if (result) {
           position.x--;
           return true;
       }

       return false;
}


bool ShortRangeUnit::moveRight()
{
     bool result = mediator->notify(shared_from_this(), MOVE_RIGHT);

       if (result) {
           position.x++;
           return true;
       }
       return false;
}


bool ShortRangeUnit::moveTop()
{
     bool result = mediator->notify(shared_from_this(), MOVE_TOP);

       if (result) {
           position.y--;
           return true;
       }

       return false;
}


bool ShortRangeUnit::moveBottom()
{
    
    bool result = mediator->notify(shared_from_this(), MOVE_BOTTOM);

    if (result) {
        position.y++;
        return true;
    }

    return false;
}

