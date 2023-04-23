#include "CavalryCreator.h"
#include "Cavalry.h"

std::shared_ptr<Unit> CavalryCreator::make_unit() const {
    return std::make_shared<Cavalry>();
}