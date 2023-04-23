#include "SpecialForcesCreator.h"
#include "military/SpecialForces.h"

std::shared_ptr<Unit> SpecialForcesCreator::make_unit() const {
    return std::make_shared<SpecialForces>();
}
