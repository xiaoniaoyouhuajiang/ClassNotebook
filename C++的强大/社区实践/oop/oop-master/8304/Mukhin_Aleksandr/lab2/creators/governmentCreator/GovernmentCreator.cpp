#include "GovernmentCreator.h"
#include "Government.h"

std::shared_ptr<Unit> GovernmentCreator::make_unit() const {
    return std::make_shared<Government>();
}