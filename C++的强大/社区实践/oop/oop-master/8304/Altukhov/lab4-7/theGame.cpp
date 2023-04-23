#include <locale>
#include <iostream>
//#include "Field.h"
//#include "Base.h"
#include <sstream>
//#include "InputProcessor.h"
#include "Game.h"
#include "EndGameWar.h"
#include "EndGameEconomics.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	srand(2);

	std::cout << "Условие для победы (0 - военная победа, 1 - экономическая победа)\n";
	int answer = 0;
	std::cin >> answer;
	try {
		if (answer == 1) {
			Game<EndGameEconomics>* game = Game<EndGameEconomics>::getGame();
			game->startGame();
			delete game;
		}
		else {
			Game<EndGameWar>* game = Game<EndGameWar>::getGame();
			game->startGame();
			delete game;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Непредвиденная ошибка!: " << e.what() << std::endl;
	}

	return 0;
}


