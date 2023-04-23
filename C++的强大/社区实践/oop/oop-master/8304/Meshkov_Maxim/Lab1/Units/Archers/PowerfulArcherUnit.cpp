#include "PowerfulArcherUnit.hpp"

std::shared_ptr<Unit> PowerfulArcherUnit::createNewOfSameType() const {
    return std::make_shared<PowerfulArcherUnit>();
}

std::shared_ptr<Unit> PowerfulArcherUnit::createCopy() const {
    auto copy = std::make_shared<PowerfulArcherUnit>();
    *copy = *this;
    return copy;
}