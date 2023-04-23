//
// Created by smokfyz on 13.05.19.
//

#include <iostream>
#include <cstdlib>
#include "StaticImpediment.h"
#include "../runtime/Game.h"

void StaticImpediment::update() {}

Mountains::Mountains()  {
    type_name = "Mountains";
    permeability = 70;
    probability = 0.5;
}

void Mountains::generate() {

}

Forest::Forest() {
    type_name = "Forest";
    permeability = 40;
    probability = 0.2;
}

void Forest::generate() {
    Game &game = Game::getGame();
    Field &field = game.getField();
}

Swamp::Swamp() {
    type_name = "Swamp";
    permeability = 60;
    probability = 0.1;
}

void Swamp::generate() {
    Game &game = Game::getGame();
    Field &field = game.getField();
}

River::River() {
    type_name = "River";
    permeability = 30;
    probability = 0.3;
}

void River::generate() {
    Game &game = Game::getGame();
    Field &field = game.getField();
}
