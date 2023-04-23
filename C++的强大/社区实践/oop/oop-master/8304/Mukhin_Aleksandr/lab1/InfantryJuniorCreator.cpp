#include "InfantryJuniorCreator.h"
#include "InfantryJunior.h"

std::shared_ptr<Unit> InfantryJuniorCreator::make_unit() const {
    return std::make_shared<InfantryJunior>();
}
