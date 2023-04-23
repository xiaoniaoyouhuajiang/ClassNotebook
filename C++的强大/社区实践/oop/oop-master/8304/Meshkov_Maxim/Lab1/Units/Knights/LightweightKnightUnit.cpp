#include "LightweightKnightUnit.hpp"

std::shared_ptr<Unit> LightweightKnightUnit::createNewOfSameType() const {
    return std::make_shared<LightweightKnightUnit>();
}

std::shared_ptr<Unit> LightweightKnightUnit::createCopy() const {
    auto copy = std::make_shared<LightweightKnightUnit>();
    *copy = *this;
    return copy;
}
