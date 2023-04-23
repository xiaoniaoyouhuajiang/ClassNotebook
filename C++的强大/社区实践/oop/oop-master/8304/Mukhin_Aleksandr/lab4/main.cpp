#include <iostream>
#include "Facade.h"


int main() {
    Boardfield a(5, 6);
    Base b(5);
    std::shared_ptr<Facade> facade = std::make_shared<Facade>(&b, &a);
    facade->fill_board();
    return 0;
}
