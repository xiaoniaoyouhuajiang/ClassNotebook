#include "EngineerCreator.h"
#include "Engineer.h"

std::shared_ptr<Unit> EngineerCreator::make_unit() const {
    return std::make_shared<Engineer>();
}
