#include "MinistryCreator.h"
#include "Ministry.h"

std::shared_ptr<Unit> MinistryCreator::make_unit() const {
    return std::make_shared<Ministry>();
}