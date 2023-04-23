#pragma once
#include "BoardUnit.h"
class Board
{
public:
	struct BoardProperties { //характеристики поля
		unsigned int maxAllowedUnits = 0;
		unsigned int sizeX = 0;
		unsigned int sizeY = 0;
	};
	struct BoardCell { //одна наша клетка
		bool isEmpty = true;
		BoardUnit* unit = nullptr;
	};
public:
	Board(BoardProperties* properties); //конструктор
	Board(Board& board); // конструктор
	void addUnit(BoardUnit* newUnit, unsigned int x, unsigned int y);
	void removeUnit(unsigned int x, unsigned int y);
	void removeUnit(BoardUnit* unit);
	void moveUnit(BoardUnit* unit, unsigned int x, unsigned int y);
	void moveUnit(unsigned int current_x, unsigned int current_y, unsigned int intended_x, unsigned int intended_y);
	void _debug_print();

	BoardUnit* operator()(unsigned int x, unsigned int y); //дестуктор
protected:
	BoardProperties* mBoardProperties = nullptr;
	BoardCell** boardArray = nullptr;
	unsigned int unitCount = 0;
	unsigned int freeCells = 0;
};

