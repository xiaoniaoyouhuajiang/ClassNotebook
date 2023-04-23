#include "Facade.hpp"

void Facade::startGame(Rules *rules) {
   // createGamer();
    manager->startGame(rules);
}

void Facade::makeAction() {
    manager->printMenu();
    manager->makeChoice();
}

void Facade::createGamer() {
    manager->createGamer();
}
