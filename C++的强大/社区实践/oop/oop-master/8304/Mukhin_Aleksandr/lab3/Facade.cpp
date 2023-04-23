#include "Facade.h"

bool Facade::fill_board() {
    board->add_base(*base, 0, 0);
    board->add_units(*base, 4, 3);
    board->add_landscapes();
    board->get_boardfield();
    std::cout << std::endl;
    base->get_base();
    return true;
}
