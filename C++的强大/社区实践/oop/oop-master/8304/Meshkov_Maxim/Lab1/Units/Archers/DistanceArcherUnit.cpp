#include "DistanceArcherUnit.hpp"

std::shared_ptr<Unit> DistanceArcherUnit::createNewOfSameType() const {
    return std::make_shared<DistanceArcherUnit>();
}

std::shared_ptr<Unit> DistanceArcherUnit::createCopy() const {
    auto copy = std::make_shared<DistanceArcherUnit>();
    *copy = *this;
    return copy;
}
