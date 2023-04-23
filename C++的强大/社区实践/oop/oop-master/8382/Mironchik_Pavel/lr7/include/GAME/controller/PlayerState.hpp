#pragma once

class GameBoard;

class PlayerState {
private:
	int _squad;
public:
	PlayerState(int squad);
	int squad();
	bool isOver(GameBoard* board);
};