#include "game.h"

void Facade::run() {
	bool flag = map->endGame();
	isRun = true;
	LOGGER.LOG("Run game");
	while (flag) {
        bool flag = map->endGame();
	}
	LOGGER.LOG("Game end");
	isRun = false;
}

