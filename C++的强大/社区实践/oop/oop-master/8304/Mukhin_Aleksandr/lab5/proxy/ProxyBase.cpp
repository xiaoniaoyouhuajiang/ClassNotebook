#include "ProxyBase.h"

void ProxyBase::add_unit(std::shared_ptr<Unit>& unit) {
    std::cout << "Adding unit!" << std::endl;
    base->add_unit(unit);
}

void ProxyBase::get_base() {
    std::cout << "Getting base!" << std::endl;
    base->get_base();
}
