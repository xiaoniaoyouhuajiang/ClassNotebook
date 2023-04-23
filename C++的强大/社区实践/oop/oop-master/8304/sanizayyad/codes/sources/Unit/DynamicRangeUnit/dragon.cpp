#include "dragon.hpp"

using namespace unit;



 Dragon::Dragon(const Position2D& position, std::shared_ptr<Mediator> mediator) :
     DynamicRangeUnit(position, mediator)
 {
     unitName = "Dragon";
     healthPoints = DRAGON_HEALTHPOINTS;
 }

 Dragon::Dragon(const Dragon& unit) : DynamicRangeUnit(unit)
 {
     this->doCopy(unit);
 }


 Dragon& Dragon::operator=(const Dragon& unit)
 {
     if (this == &unit) {
         return *this;
     }

     this->doCopy(unit);

     return *this;
 }


 std::shared_ptr<Unit> Dragon::clone()
 {
     std::shared_ptr<Unit> unit(new Dragon(*this));
     return unit;
 }
