#include "InfantrySeniorCreator.h"
#include "InfantrySenior.h"

std::shared_ptr<Unit> InfantrySeniorCreator::make_unit() const {
    return std::make_shared<InfantrySenior>();
}
