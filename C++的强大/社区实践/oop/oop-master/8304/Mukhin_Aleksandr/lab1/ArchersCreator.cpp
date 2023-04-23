#include "ArchersCreator.h"
#include "Archers.h"

std::shared_ptr<Unit> ArchersCreator::make_unit() const {
    return std::make_shared<Archers>();
}