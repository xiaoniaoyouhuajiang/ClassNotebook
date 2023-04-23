#include <iostream>

#include "Facade.hpp"

int main() {

    auto f = new Facade;
    f->startGame();
    f->makeAction();

    return 0;
}
