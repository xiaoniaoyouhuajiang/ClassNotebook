#include "Base.h"


void Base::add_unit(std::shared_ptr<Unit>& unit) {
    units.emplace_back(unit);
    current_size++;
}


void Base::get_base() {
    for (const auto& unit : units) {
        if (unit->x != -1 ) {
            std::cout << "♘(" << unit->get_health() << ", " << unit->get_attack() << ", " << unit->get_intelligence() << ")    " << std::endl;
        }
    }
}


void Base::interaction() const {
    mediator->make_action();
}
