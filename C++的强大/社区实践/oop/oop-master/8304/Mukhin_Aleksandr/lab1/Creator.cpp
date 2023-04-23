#include "Creator.h"

char Creator::SomeOperation() const {
    std::shared_ptr<Unit> unit = this->make_unit();
    char result = unit->greeting();
    return result;
}
