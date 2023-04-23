#include "Civilians.h"
#include "CiviliansCreator.h"

std::shared_ptr<Unit> CiviliansCreator::make_unit() const {
    return std::make_shared<Civilians>();
}