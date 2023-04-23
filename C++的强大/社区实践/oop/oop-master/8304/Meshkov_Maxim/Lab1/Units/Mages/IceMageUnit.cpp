#include "IceMageUnit.hpp"

std::shared_ptr<Unit> IceMageUnit::createNewOfSameType() const {
    return std::make_shared<IceMageUnit>();
}

std::shared_ptr<Unit> IceMageUnit::createCopy() const {
    auto copy = std::make_shared<IceMageUnit>();
    *copy = *this;
    return copy;
}
