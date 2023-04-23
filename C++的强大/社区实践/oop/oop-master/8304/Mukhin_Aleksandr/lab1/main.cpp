#include <iostream>
#include "Boardfield.h"

int main() {
    Boardfield a(6, 8);

    a.add_unit_at(4, 3, 4);
    a.add_unit_at(2, 5, 2);
    a.add_unit_random(2);
    a.add_unit_random(2);
    a.move(5, 2, 1, 4);

    Boardfield b = a;

    a.delete_unit(1, 4);

    a.get_board();
    std::cout << std::endl;
    b.get_board();
    return 0;
}
