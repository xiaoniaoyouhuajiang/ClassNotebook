#include "neutralobject.hpp"

using namespace unit;
void NeutralObject::operator[](std::shared_ptr<unit::Unit> unit)
{
    selectLogic(unit);
    strategyPattern->updateUnit(unit);
}
