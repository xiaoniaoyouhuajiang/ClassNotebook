#include "Facade.hpp"

void Facade::startGame() {
    manager->startGame();
}

void Facade::makeAction() {
    manager->printMenu();
    manager->makeChoice();
}
