#include "Board.h"
#include <QDebug>
#include <string>

Board::Board(BoardProperties* properties) : mBoardProperties(properties) { //наше поле
	boardArray = new BoardCell* [properties->sizeY]; //массив пео иксам
	for (int i = 0; i < properties->sizeY; i++) {
		BoardCell* tCellArray = new BoardCell[properties->sizeX]; //массив по игрикам
		boardArray[i] = tCellArray;
	}
	//горы, вулканы и тд
}

void Board::addUnit(BoardUnit* newUnit, unsigned int x, unsigned int y) {
	BoardCell* tCell = &(boardArray[y][x]); //tCell - наша клетка
	if (unitCount >= mBoardProperties->maxAllowedUnits) {
		//throw
		return;
	}
	if (!tCell->isEmpty) {
		//throw
		return;
	}
	tCell->isEmpty = false;
	tCell->unit = newUnit;
	unitCount++;
}

void Board::removeUnit(unsigned int x, unsigned int y) {
	BoardCell* tCell = &(boardArray[y][x]);
	if (tCell->isEmpty) {
		//throw
		return;
	}
	tCell->isEmpty = true;
	tCell->unit = nullptr;
}

void Board::removeUnit(BoardUnit* unit) {
	BoardCell* tCell = nullptr;
	for (int i = 0; i < mBoardProperties->sizeY; i++) {
		for (int j = 0; j < mBoardProperties->sizeX; j++) {
			if (boardArray[i][j].unit == unit) {
				tCell = &boardArray[i][j];
			}
		}
	}
	if (tCell == nullptr || tCell->isEmpty) {
		//throw
		return;
	}
	tCell->isEmpty = true;
	tCell->unit = nullptr;
}

BoardUnit* Board::operator()(unsigned int x, unsigned int y) { //перегрузка
	if (x > mBoardProperties->sizeX || y > mBoardProperties->sizeY) {
		//throw
		return nullptr;
	}
	return boardArray[y][x].unit;
}

Board::Board(Board& board) : unitCount(board.unitCount), freeCells(board.freeCells)
{
	mBoardProperties = new BoardProperties(*(board.mBoardProperties));
	boardArray = new BoardCell * [mBoardProperties->sizeY];
	for (int i = 0; i < mBoardProperties->sizeY; i++) {
		BoardCell* tCellArray = new BoardCell[mBoardProperties->sizeX];
		boardArray[i] = tCellArray;
		for (int j = 0; j < mBoardProperties->sizeX; j++) {
			if (!board.boardArray[i][j].isEmpty) {
				boardArray[i][j].isEmpty = false;
				boardArray[i][j].unit = board.boardArray[i][j].unit->getCopy();
			}
		}
	}
}

void Board::moveUnit(BoardUnit* unit, unsigned int x, unsigned int y) {
	BoardCell* fromCell = nullptr;
	BoardCell* toCell = &boardArray[y][x];
	for (int i = 0; i < mBoardProperties->sizeY; i++) {
		for (int j = 0; j < mBoardProperties->sizeX; j++) {
			if (boardArray[i][j].unit == unit) {
				fromCell = &boardArray[i][j];
			}
		}
	}
	if (fromCell == nullptr || fromCell->isEmpty || !toCell->isEmpty) {
		//throw
		return;
	}
	toCell->isEmpty = false;
	toCell->unit = fromCell->unit;
	fromCell->unit = nullptr;
	fromCell->isEmpty = true;
}

void Board::moveUnit(unsigned int current_x, unsigned int current_y, unsigned int intended_x, unsigned int intended_y) {
	BoardCell* fromCell = &boardArray[current_y][current_x];;
	BoardCell* toCell = &boardArray[intended_y][intended_x];
	if (fromCell->isEmpty || !toCell->isEmpty) {
		//throw
		return;
	}
	toCell->isEmpty = false;
	toCell->unit = fromCell->unit;
	fromCell->unit = nullptr;
	fromCell->isEmpty = true;
}

void Board::_debug_print() {
	qInfo() << "--------------------Board start----------------------";
	for (int i = 0; i < mBoardProperties->sizeY; i++) {
		std::string tstr;
		for (int j = 0; j < mBoardProperties->sizeX; j++) {
			if (boardArray[i][j].isEmpty) {
				tstr += "[ ]";
			}
			else
				tstr += "[X]";
			tstr += " ";
		}
		qInfo() << " ";
		qInfo() << tstr.c_str();
	}
	qInfo() << "--------------------Board end----------------------";
	qInfo() << " ";
}




