#include "AirborneCreator.h"
#include "Airborne.h"

std::shared_ptr<Unit> AirborneCreator::make_unit() const {
    return std::make_shared<Airborne>();
}
