#include "FireMageUnit.hpp"

std::shared_ptr<Unit> FireMageUnit::createNewOfSameType() const {
    return std::make_shared<FireMageUnit>();
}

std::shared_ptr<Unit> FireMageUnit::createCopy() const {
    auto copy = std::make_shared<FireMageUnit>();
    *copy = *this;
    return copy;
}