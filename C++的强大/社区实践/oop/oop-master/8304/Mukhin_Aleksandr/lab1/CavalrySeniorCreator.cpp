#include "CavalrySeniorCreator.h"
#include "CavalrySenior.h"

std::shared_ptr<Unit> CavalrySeniorCreator::make_unit() const {
    return std::make_shared<CavalrySenior>();
}
