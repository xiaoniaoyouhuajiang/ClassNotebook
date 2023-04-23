#include <GAME/controller/Rules2.hpp>
#include <GAME/controller/MapConstructor.hpp>
#include <GAME/engine/GameBoard.hpp>
#include <GAME/engine/terrains/GroundTerrain.hpp>

GameBoard* Rules2::makeBoard() {
	GameBoard* board = new GameBoard(20, 20, 1000, 600);
	MapConstructor::circle<GroundTerrain>(board, sf::Vector2i(3, 3), 5);
	MapConstructor::circle<GroundTerrain>(board, sf::Vector2i(16, 16), 5);
	MapConstructor::circle<GroundTerrain>(board, sf::Vector2i(10, 10), 6);
	MapConstructor::circle<LavaTerrain>(board, sf::Vector2i(10, 10), 4);
	board->getController().addUnit(board->getController().createHome(0), sf::Vector2i(3, 3));
	board->getController().addUnit(board->getController().createHome(1), sf::Vector2i(16, 16));
	return board;
}