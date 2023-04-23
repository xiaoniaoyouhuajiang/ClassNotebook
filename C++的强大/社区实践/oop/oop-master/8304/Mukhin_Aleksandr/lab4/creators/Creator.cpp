#include "Creator.h"

void Creator::greeting() const {
    std::shared_ptr<Unit> unit = this->make_unit();
    unit->greeting();
}
