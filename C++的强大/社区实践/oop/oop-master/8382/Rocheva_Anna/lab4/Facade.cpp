#include "Facade.hpp"

void Facade::startGame() {
    createGamer();
    manager->startGame();
}

void Facade::makeAction() {
    manager->printMenu();
    manager->makeChoice();
}

void Facade::createGamer() {
    manager->createGamer();
}
