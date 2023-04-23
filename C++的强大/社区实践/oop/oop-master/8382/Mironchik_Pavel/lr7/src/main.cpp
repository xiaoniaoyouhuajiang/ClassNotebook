#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <SFML/Graphics/Text.hpp>
#include <GAME/engine/units/BumSoldier.hpp>
#include <GAME/engine/units/Peasant.hpp>
#include <GAME/engine/units/Stone.hpp>
#include <GAME/engine/units/Heal.hpp>
#include <GAME/engine/units/Chancel.hpp>
#include <GAME/engine/units/BlackHole.hpp>
#include <GAME/engine/Unit.hpp>
#include <GAME/engine/Info.hpp>
#include <chrono>
#include <iostream>
#include <cstdlib>
#include <GAME/engine/terrains/GroundTerrain.hpp>
#include <GAME/log/FileLogAdapter.hpp>
#include <GAME/serialize/GameSerializer.hpp>
#include <GAME/controller/GameControllerImp1.hpp>
#include <GAME/utils/Fonts.hpp>

void run();

int main() {
	GameController::instance(GameControllerImp1_2::instance());
	GameController::instance()->newGame();

	try {
		run();
	}
	catch (const LogInfo& exception) {
		Log::log("Exception was thrown");
		Log::log(exception);
		system("pause");
	}
	catch (...) {
		Log::log("Unknown exception was thrown");
		system("pause");
	}

	return 0;
}

void run() {
	int width = 1000, height = 600;
	sf::RenderWindow window(sf::VideoMode(width, height), "15");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(false);
	clock_t time = clock();

	while (window.isOpen()) {
		sf::Event event;

		clock_t newTime = clock();
		long delta = static_cast<long>(newTime - time) * 1000 / CLOCKS_PER_SEC;

		window.clear(sf::Color(255, 255, 255));

		GameController::instance()->board()->onFrameStart();
		while (window.pollEvent(event)) {
			/*if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F1) {
				GameSerializer().write(board);
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F2) {
				auto newBoard = GameSerializer().read();

				if (newBoard != nullptr) {
					delete board;
					board = newBoard;
				}
			}*/

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F4) {

				LogInfo info;
				info.name = "Test";
				throw info;

				GameController::instance(GameControllerImp1_2::instance());
				GameController::instance()->newGame();
			}

			if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F5) {
				GameController::instance(GameControllerImp1_3::instance());
				GameController::instance()->newGame();
			}

			if (!GameController::instance()->isOver())
				GameController::instance()->board()->onEvent(event);
		}
		GameController::instance()->board()->onFrame(delta);
		window.draw(*GameController::instance()->board());
		GameController::instance()->board()->onFrameEnd();

		sf::Text fps;
		fps.setFillColor(sf::Color(0, 0, 0));
		fps.setFont(Fonts::instance().main());
		fps.setCharacterSize(20);
		fps.setPosition(width - 100, 10);
		fps.setString(std::to_string(delta > 0 ? 1000 / delta : 0));
		window.draw(fps);

		if (GameController::instance()->isOver()) {
			sf::Text gameOver;
			gameOver.setFillColor(sf::Color(0, 0, 0));
			gameOver.setFont(Fonts::instance().main());
			gameOver.setCharacterSize(50);
			gameOver.setPosition(width / 2 - 100, height / 2 - 70);
			gameOver.setString("GAME OVER");
			window.draw(gameOver);

			gameOver.setPosition(width / 2 - 100, height / 2);
			gameOver.setCharacterSize(30);
			gameOver.setString("Press F4 or F5 to start new game");
			window.draw(gameOver);
		}

		time = newTime;

		window.display();
	}
}