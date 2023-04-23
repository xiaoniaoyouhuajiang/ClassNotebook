#include "HeavyKnightUnit.hpp"

std::shared_ptr<Unit> HeavyKnightUnit::createNewOfSameType() const {
    return std::make_shared<HeavyKnightUnit>();
}

std::shared_ptr<Unit> HeavyKnightUnit::createCopy() const {
    auto copy = std::make_shared<HeavyKnightUnit>();
    *copy = *this;
    return copy;
}
