#include "GameDestroyer.h"
#include "Game.h"

GameDestroyer::~GameDestroyer() {
    delete game;
}

void GameDestroyer::init(Game* game) {
    this->game = game;
}
