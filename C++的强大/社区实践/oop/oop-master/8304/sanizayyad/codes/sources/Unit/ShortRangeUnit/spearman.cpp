#include "spearman.hpp"

using namespace unit;

 SpearMan::SpearMan(const Position2D& position, std::shared_ptr<Mediator> mediator) :
     ShortRangeUnit(position, mediator)
 {
     unitName = "SpearMan";
     healthPoints = SHORT_RANGE_HEALTHPOINTS;
 }


 SpearMan::SpearMan(const SpearMan& unit) : ShortRangeUnit(unit)
 {
     this->doCopy(unit);
 }


 SpearMan& SpearMan::operator=(const SpearMan& unit)
 {
     if (this == &unit) {
         return *this;
     }

     this->doCopy(unit);

     return *this;
 }


 std::shared_ptr<Unit> SpearMan::clone()
 {
     std::shared_ptr<Unit> unit(new SpearMan(*this));
     return unit;
 }
