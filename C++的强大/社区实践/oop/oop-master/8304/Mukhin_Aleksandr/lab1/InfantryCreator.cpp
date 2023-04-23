#include "InfantryCreator.h"

std::shared_ptr<Unit> InfantryCreator::make_unit() const{
    return std::make_shared<Infantry>();
}