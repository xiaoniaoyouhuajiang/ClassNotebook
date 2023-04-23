#include "vampire.hpp"

using namespace unit;

 Vampire::Vampire(const Position2D& position, std::shared_ptr<Mediator> mediator) :
     DynamicRangeUnit(position, mediator)
 {
     unitName = "Vampire";
     healthPoints = VAMPIRE_HEALTHPOINTS;
 }

 Vampire::Vampire(const Vampire& unit) : DynamicRangeUnit(unit)
 {
     this->doCopy(unit);
 }


 Vampire& Vampire::operator=(const Vampire& unit)
 {
     if (this == &unit) {
         return *this;
     }

     this->doCopy(unit);

     return *this;
 }


 std::shared_ptr<Unit> Vampire::clone()
 {
     std::shared_ptr<Unit> unit(new Vampire(*this));
     return unit;
 }
