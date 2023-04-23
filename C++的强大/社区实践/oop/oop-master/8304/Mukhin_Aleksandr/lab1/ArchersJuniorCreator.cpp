#include "ArchersJuniorCreator.h"
#include "ArchersJunior.h"

std::shared_ptr<Unit> ArchersJuniorCreator::make_unit() const {
    return std::make_shared<ArchersJunior>();
}
