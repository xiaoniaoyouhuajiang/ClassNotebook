#include "pch.h"
#include "Game.h"

int main(int argc, const char *atgv[]) {
	int newGameRequest;
	Game<DewDomination> *game = Game<DewDomination>::getInstance();
	game->newGame();
	newGameRequest = game->gameCycle();

	while (newGameRequest) {
		game->newGame();
		newGameRequest = game->gameCycle();
	}

	return 0;
}