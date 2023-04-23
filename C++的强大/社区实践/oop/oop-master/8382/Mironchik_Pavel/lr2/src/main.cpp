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
#include <GAME/engine/terrains/GroundTerrain.hpp>

// using namespace std::chrono;

// milliseconds getMilliseconds();

int main() {
	int width = 1000, height = 600;
	sf::RenderWindow window(sf::VideoMode(width, height), "15");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(false);

	GameBoard* board = new GameBoard(20, 20, 1000, 600);
	sf::Font font;
	font.loadFromFile("D:\\University\\3_course\\OOP\\Game\\SimpleGame\\Debug\\assets\\fonts\\arial.ttf");
	sf::Text text;
	text.setFillColor(sf::Color(0, 0, 0));
	text.setFont(font);
	text.setCharacterSize(20);
	text.setPosition(width - 100, 10);
	sf::Color color = sf::Color(255, 255, 255);
	clock_t time = clock();

	for (int x = 0; x < 20; x++)
		for (int y = 0; y < 20; y++) {
			Terrain* terrain;

			if (y < 5) terrain = new SeaTerrain();
			else if (y < 15) terrain = new GroundTerrain();
			else terrain = new LavaTerrain();

			auto ptr = shared_ptr<Terrain>(terrain);
			board->getCell(sf::Vector2i(x, y)).terrain(ptr);
		}

	for (int i = 0; i < 10; i++) {
		auto soldier = board->getController().createBoomSoldier(i);
		board->getController().addUnit(soldier, sf::Vector2i(10 + i / 5, 10 + i % 5));
	}

	auto stone = board->getController().createStone();
	board->getController().addNeutral(stone, sf::Vector2i(10, 5));

	auto heal = board->getController().createHeal();
	board->getController().addNeutral(heal, sf::Vector2i(11, 5));

	auto chancel = board->getController().createChancel();
	board->getController().addNeutral(chancel, sf::Vector2i(12, 5));

	auto home = board->getController().createUnit(Info::HOME, 1);
	board->getController().addUnit(home, sf::Vector2i(5, 5));

	auto blackHole = board->getController().createBlackHole();
	board->getController().addNeutral(blackHole, sf::Vector2i(13, 5));

	while (window.isOpen()) {
		sf::Event event;
		
		clock_t newTime = clock();
		long delta = static_cast<long>(newTime - time) * 1000 / CLOCKS_PER_SEC;

		window.clear(color);

		board->onFrameStart();
		while (window.pollEvent(event)) {
			board->onEvent(event);
		}
		board->onFrame(delta);
		window.draw(*board);
		board->onFrameEnd();

		text.setString(std::to_string(delta > 0 ? 1000 / delta : 0));
		window.draw(text);

		time = newTime;

		window.display();
	}

	return 0;
}

long getMilliseconds() {
	return clock() / CLOCKS_PER_SEC * 1000;
	/*return duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);*/
}