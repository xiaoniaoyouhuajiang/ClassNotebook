#include "MilitaryCreator.h"
#include "Military.h"

std::shared_ptr<Unit> MilitaryCreator::make_unit() const {
    return std::make_shared<Military>();
}