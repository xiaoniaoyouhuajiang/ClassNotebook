#include "archer.hpp"

using namespace unit;


 Archer::Archer(const Position2D& position, std::shared_ptr<Mediator> mediator) :
     LongRangeUnit(position, mediator)
 {
     unitName = "Archer";
     healthPoints = ARCHER_HEALTHPOINTS;
 }

 Archer::Archer(const Archer& unit) : LongRangeUnit(unit)
 {
     this->doCopy(unit);
 }


 Archer& Archer::operator=(const Archer& unit)
 {
     if (this == &unit) {
         return *this;
     }

     this->doCopy(unit);

     return *this;
 }


 std::shared_ptr<Unit> Archer::clone()
 {
     std::shared_ptr<Unit> unit(new Archer(*this));
     return unit;
 }
