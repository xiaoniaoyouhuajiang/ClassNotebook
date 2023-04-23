#include <GAME/controller/Rules3.hpp>
#include <GAME/controller/MapConstructor.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/engine/terrains/GroundTerrain.hpp>

GameBoard* Rules3::makeBoard() {
	GameBoard* board = new GameBoard(20, 20, 1000, 600);
	MapConstructor::circle<GroundTerrain>(board, sf::Vector2i(2, 2), 5);
	MapConstructor::circle<GroundTerrain>(board, sf::Vector2i(18, 5), 5);
	MapConstructor::circle<GroundTerrain>(board, sf::Vector2i(6, 18), 6);
	MapConstructor::circle<LavaTerrain>(board, sf::Vector2i(10, 10), 4);
	board->getController().addUnit(board->getController().createHome(0), sf::Vector2i(2, 2));
	board->getController().addUnit(board->getController().createHome(1), sf::Vector2i(18, 5));
	board->getController().addUnit(board->getController().createHome(2), sf::Vector2i(6, 18));
	return board;
}