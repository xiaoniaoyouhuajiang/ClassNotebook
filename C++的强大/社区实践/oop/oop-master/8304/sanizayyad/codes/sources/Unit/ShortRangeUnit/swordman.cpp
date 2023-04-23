#include "swordman.hpp"

using namespace unit;


 SwordMan::SwordMan(const Position2D& position, std::shared_ptr<Mediator> mediator) :
     ShortRangeUnit(position, mediator)
 {
     unitName = "SwordMan";
     healthPoints = SHORT_RANGE_HEALTHPOINTS;
 }

 SwordMan::SwordMan(const SwordMan& unit) : ShortRangeUnit(unit)
 {
     this->doCopy(unit);
 }


 SwordMan& SwordMan::operator=(const SwordMan& unit)
 {
     if (this == &unit) {
         return *this;
     }

     this->doCopy(unit);

     return *this;
 }


 std::shared_ptr<Unit> SwordMan::clone()
 {
     std::shared_ptr<Unit> unit(new SwordMan(*this));
     return unit;
 }

