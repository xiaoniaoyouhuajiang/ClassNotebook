#include "ballistic.hpp"

using namespace unit;


 Ballistic::Ballistic(const Position2D& position, std::shared_ptr<Mediator> mediator) :
     LongRangeUnit(position, mediator)
 {
     unitName = "Ballistic";
     healthPoints = BALLISTICS_HEALTHPOINTS;
 }


 Ballistic::Ballistic(const Ballistic& unit) : LongRangeUnit(unit)
 {
     this->doCopy(unit);
 }


 Ballistic& Ballistic::operator=(const Ballistic& unit)
 {
     if (this == &unit) {
         return *this;
     }

     this->doCopy(unit);

     return *this;
 }


 std::shared_ptr<Unit> Ballistic::clone()
 {
     std::shared_ptr<Unit> unit(new Ballistic(*this));
     return unit;
 }
