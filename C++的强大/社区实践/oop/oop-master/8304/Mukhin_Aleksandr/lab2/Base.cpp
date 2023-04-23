#include "Base.h"
#include "military/SpecialForces.h"

void Base::add_unit(std::shared_ptr<Unit>& unit) {
    units.emplace_back(unit);
    current_size++;
}

Base::Base(int size) {
    max_size = size;
}

void Base::get_base() {
    for (const auto& unit : units) {
        if (unit->x != -1 ) {
            std::cout << "♘(" << unit->defense.get_health() << ", " << unit->attack.get_attack() << ", " << unit->intelligence << ")    " << std::endl;
        }
    }
}
