#include <iostream>
#include "Game/GameSingleton.h"

int main() {
    system("chcp 65001");

	GameSingleton game;
	game.startGame();

	return 0;
}