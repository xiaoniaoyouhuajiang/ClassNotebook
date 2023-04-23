#include "Ambassador.h"
#include "AmbassadorCreator.h"

std::shared_ptr<Unit> AmbassadorCreator::make_unit() const {
    return std::make_shared<Ambassador>();
}