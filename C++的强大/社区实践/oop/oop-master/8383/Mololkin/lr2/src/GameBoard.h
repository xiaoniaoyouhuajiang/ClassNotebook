#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include "Cell.h"
#include "Base.h"

class ObserverManager;

class GameBoard
{
private:
	ObserverManager* observerManager;
	Base* base1;
	Base* base2;
	int baseNum = 0;
	int maxBaseNum = 2;
	int length;
	int width;
	int unitsOnBoard = 0;
	int maxUnitsOnBoard;
	Cell *** board;
	void addBase(Base* baseToAdd, std::pair<int, int> pos);
	void delBase(Base* base);

public:
	GameBoard(int length, int width);
	~GameBoard();
	GameBoard(const GameBoard& other);
	GameBoard(GameBoard&& other) noexcept;
	int getLength();
	int getWidth();
	Cell*** getBoard();
	bool checkPossetion(std::pair<int, int> pos);
	void createUnit(int baseNum, Units unitType, std::pair<int, int> pos);
	void delUnit(std::pair<int, int> pos);
	void moveUnit(std::pair<int, int> pos1, std::pair<int, int> pos2);
	std::string getLine(int lineNum);
};

