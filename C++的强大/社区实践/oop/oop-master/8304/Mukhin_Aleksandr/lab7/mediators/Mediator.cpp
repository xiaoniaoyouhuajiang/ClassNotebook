#include "Mediator.h"

void Mediator::make_action() const {
    std::cout << "Interaction!" << std::endl;
    if (command == "unit action") {
        elem2->change_health(-elem1->get_attack());
    } else if (command == "base action") {
        elem2->change_health(-base->get_attack());
    } else {
        elem1->change_health(elem2->get_health());
        elem1->change_attack(elem2->get_attack());
        elem1->change_intelligence(elem2->get_intelligence());
    }
}
