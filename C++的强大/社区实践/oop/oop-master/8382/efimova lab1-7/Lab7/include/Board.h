#pragma once
#include <QJsonArray>
#include <QJsonObject>

#include "BoardUnit.h"
#include "TerrainBoardUnit.h"
#include "Grass.h"
#include "Snow.h"
#include "River.h"
#include "Stone.h"
#include "Tree.h"
#include "TreeLog.h"
class Board
{
public:
	struct BoardProperties {
		int maxAllowedUnits = 0;
		int sizeX = 0;
		int sizeY = 0;
	};
	struct BoardCell {
		bool isEmpty = true;
		BoardUnit* unit = nullptr;
		TerrainBoardUnit* terrainUnit = nullptr;
		int x;
		int y;
	};
public:
	Board(BoardProperties* properties);
	Board(QJsonObject snapshot);
	void addUnit(BoardUnit* newUnit, unsigned int x, unsigned int y);
	void removeUnit(unsigned int x, unsigned int y);
	void removeUnit(BoardUnit* unit);
	void moveUnit(BoardUnit* unit, unsigned int x, unsigned int y);
	void moveUnit(unsigned int current_x, unsigned int current_y, unsigned int intended_x, unsigned int intended_y);
	std::pair<int, int> getUnitCoords(BoardUnit* unit);
	BoardProperties getBoardProperties();
	QJsonObject getSnapshot();

	void _debug_print();

	BoardUnit* operator()(unsigned int x, unsigned int y);
	BoardCell getCellAt(unsigned int x, unsigned int y);
protected:
	BoardProperties* mBoardProperties = nullptr;
	BoardCell** boardArray = nullptr;
	unsigned int unitCount = 0;
	unsigned int freeCells = 0;
};

