#include "CavalryJuniorCreator.h"
#include "CavalryJunior.h"

std::shared_ptr<Unit> CavalryJuniorCreator::make_unit() const {
    return std::make_shared<CavalryJunior>();
}
