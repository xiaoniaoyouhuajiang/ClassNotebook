#include <iostream>
#include "Base.h"
#include "Boardfield.h"


int main() {
    Boardfield a(5, 6);
    Base b(5);
    a.add_base(b, 0, 0);
    a.add_unit(b, 0, 1, 0);
    a.add_unit(b, 0, 2, 0);
    a.add_neutral_object(0, 1, 0);

    a.add_landscapes();

    a.get_boardfield();
    std::cout << std::endl;
    b.get_base();

    a.attack(0, 1, 0, 2);

    a.get_boardfield();
    std::cout << std::endl;
    b.get_base();

    return 0;
}
