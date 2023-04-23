#pragma once

#include <GAME/log/FileSession.hpp>

class GameBoard;

class GameSerializer {
private:
	std::string _filename;

public:
	GameSerializer(std::string filename = "saved.hehe");
	void write(GameBoard* board);
	GameBoard* read();
};