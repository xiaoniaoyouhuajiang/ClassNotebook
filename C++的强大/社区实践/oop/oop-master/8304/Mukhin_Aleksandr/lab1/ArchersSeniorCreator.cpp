#include "ArchersSeniorCreator.h"
#include "ArchersSenior.h"

std::shared_ptr<Unit> ArchersSeniorCreator::make_unit() const {
    return std::make_shared<ArchersSenior>();
}
