#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include "Cell.h"
#include "Base.h"
#include "Logger.h"

class ObserverManager;

class GameBoard
{
private:
	ObserverManager* observerManager;
	int baseNum = 0;
	int maxBaseNum = 3;
	int length;
	int width;
	int unitsOnBoard = 0;
	int maxUnitsOnBoard;
	Cell *** board;
	Base* base1;
	Base* base2;
	

public:
	Base* getBase1();
	Base* getBase2();
	void addBase(Base* baseToAdd, std::pair<int, int> pos);
	void delBase(Base* base);
	GameBoard(int length, int width);
	~GameBoard();
	GameBoard(const GameBoard& other);
	GameBoard(GameBoard&& other) noexcept;
	int getLength();
	int getWidth();
	Cell*** getBoard();
	bool checkPossetion(std::pair<int, int> pos);
	bool createUnit(int baseNum, Units unitType, std::pair<int, int> pos, LoggerProxy* logger);
	void delUnit(std::pair<int, int> pos);
	bool moveUnit(std::pair<int, int> pos1, std::pair<int, int> pos2, LoggerProxy* logger);
	std::string getLine(int lineNum);
};

