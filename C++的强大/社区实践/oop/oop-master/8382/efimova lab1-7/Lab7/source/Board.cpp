#include "Board.h"
#include "PongoBoardUnit.h"
#include "Reputeless/PerlinNoise.hpp"	//Perlin noise header library
#include <QDebug>
#include <string>
#include "PongoBaseBoardUnit.h"
#include "GameException.h"// подкл. наши исключения

Board::Board(BoardProperties* properties) : mBoardProperties(properties) {
	boardArray = new BoardCell * [properties->sizeY];
	for (int i = 0; i < properties->sizeY; i++) {
		BoardCell* tCellArray = new BoardCell[properties->sizeX];
		boardArray[i] = tCellArray;
	}
	siv::PerlinNoise mNoise;
	std::random_device rd;
	std::mt19937_64 mt_rand(rd());
	std::uniform_int_distribution<> rand_1(0, mBoardProperties->sizeX * mBoardProperties->sizeY);
	std::uniform_int_distribution<> rand_2(1, 4);
	mNoise.reseed(mt_rand());	
	for (int i = 0; i < mBoardProperties->sizeY; i++) {
		for (int j = 0; j < mBoardProperties->sizeX; j++) {
			boardArray[i][j].x = j;
			boardArray[i][j].y = i;
			//auto value = mNoise.normalizedOctaveNoise2D_0_1((double)j/10, (double)i/10, 100);
			auto value = mNoise.normalizedOctaveNoise2D_0_1((double)j / 10, (double)i / 10, 1000);
			if(value >= 0.55)
				boardArray[i][j].terrainUnit = new Snow();
			else if (value < 0.55 && value >= 0.4)
				boardArray[i][j].terrainUnit = new Grass();
			else
				boardArray[i][j].terrainUnit = new River();

			if (rand_1(mt_rand) <= (double)mBoardProperties->sizeX * (double)mBoardProperties->sizeY * 0.05 && boardArray[i][j].isEmpty && boardArray[i][j].terrainUnit->getName() != "river") {
				switch (rand_2(mt_rand)) {
				case 1:
					boardArray[i][j].unit = new Stone();
					boardArray[i][j].isEmpty = false;
					break;
				case 2:
					boardArray[i][j].unit = new Tree();
					boardArray[i][j].isEmpty = false;
					break;
				case 3:
					boardArray[i][j].unit = new TreeLog();
					boardArray[i][j].isEmpty = false;
					break;
				default:
					break;
				}
			}
		}
	}
}

void Board::addUnit(BoardUnit* newUnit, unsigned int x, unsigned int y) {
	qInfo() << "Adding unit" << newUnit->getName().c_str() << "at" << x << y;
	BoardCell* tCell = &(boardArray[y][x]);
	if (unitCount >= mBoardProperties->maxAllowedUnits) { // выводим - кол-во юнитов на доске меньше
		throw GameException("Board error: tried to add unit when maximum number of units is reached", "Board.cpp", 62, "Board::addUnit", "isk");
		return;
	}
	if (!tCell->isEmpty) {
		//throw
		qInfo() << "Board error: tried to add unit inside a non-empty cell";
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
		qInfo() << "Board error: tried to remove unit from an empty cell";
		return;
	}
	tCell->isEmpty = true;
	tCell->unit = nullptr;
	unitCount--;
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
		qInfo() << "Board error: tried to remove unit from an empty cell";
		return;
	}
	tCell->isEmpty = true;
	tCell->unit = nullptr;
}

BoardUnit* Board::operator()(unsigned int x, unsigned int y) {
	if (x > mBoardProperties->sizeX || y > mBoardProperties->sizeY) {
		//throw
		return nullptr;
	}
	return boardArray[y][x].unit;
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
		qInfo() << "Board error: tried to move unit but something went wrong";
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
		qInfo() << "Board error: tried to move unit but something went wrong";
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
	qInfo() << " ";
	qInfo() << "--------------------Board end----------------------";
	qInfo() << " ";
}

Board::BoardCell Board::getCellAt(unsigned int x, unsigned int y) {
	return boardArray[y][x];
}

std::pair<int, int> Board::getUnitCoords(BoardUnit* unit) {
	std::pair<int, int> coords;
	for (int i = 0; i < mBoardProperties->sizeY; i++) {
		for (int j = 0; j < mBoardProperties->sizeX; j++) {
			if (boardArray[i][j].unit == unit || boardArray[i][j].terrainUnit == unit) {
				coords = std::pair<int, int>(j, i);
			}
		}
	}
	return coords;
}

Board::BoardProperties Board::getBoardProperties() {
	return *mBoardProperties;
}

QJsonObject Board::getSnapshot() {
	QJsonObject boardState;
	QJsonObject boardProperties;
	boardProperties.insert("maxAllowedUnits", mBoardProperties->maxAllowedUnits);
	boardProperties.insert("sizeX", mBoardProperties->sizeX);
	boardProperties.insert("sizeY", mBoardProperties->sizeY);
	boardState.insert("boardProperties", boardProperties);

	std::vector<std::pair<int, int>> playableUnits;

	//the real fun begins here
	//first pass without playable units except bases
	QJsonArray boardArray;
	for (int i = 0; i < mBoardProperties->sizeY; i++) {
		QJsonArray boardRow;
		for (int j = 0; j < mBoardProperties->sizeX; j++) {
			auto cell = getCellAt(j, i);

			QJsonObject cellObject;
			auto terrainUnitSnapshot = cell.terrainUnit->getSnapshot();
			cellObject.insert("terrainUnit", terrainUnitSnapshot);

			if (cell.unit == nullptr) {
				QJsonObject unit;
				unit.insert("type", "empty");
				cellObject.insert("unit", unit);
			}
			else if (dynamic_cast<PongoBoardUnit*>(cell.unit) != nullptr) {
				QJsonObject unit;
				cellObject.insert("unit", unit);
				playableUnits.push_back(std::pair<int, int>(cell.x, cell.y));
			}
			else
				cellObject.insert("unit", cell.unit->getSnapshot());
			boardRow.append(cellObject);
		}
		boardArray.append(boardRow);
	}
	//second pass, push all units into their corresponding bases
	for (int i = 0; i < playableUnits.size(); i++) {
		auto unit = getCellAt(playableUnits[i].first, playableUnits[i].second).unit;

		auto unitSnapshot = unit->getSnapshot();
		unitSnapshot.insert("x", playableUnits[i].first);
		unitSnapshot.insert("y", playableUnits[i].second);
		int baseX = unitSnapshot["base"].toObject()["x"].toInt();
		int baseY = unitSnapshot["base"].toObject()["y"].toInt();

		//this is fucking retarded, but Qt doesn't allow modifying nested Jsons
		auto row = boardArray[baseY].toArray();
		auto cell = row[baseX].toObject();
		auto base = cell["unit"].toObject();
		auto units = base["units"].toArray();
		units.append(unitSnapshot);
		base["units"] = units;
		cell["unit"] = base;
		row[baseX] = cell;
		boardArray[baseY] = row;

	}
	boardState.insert("boardArray", boardArray);
	return boardState;
}

Board::Board(QJsonObject snapshot) {
	auto boardProperties = snapshot["boardProperties"].toObject();
	auto boardArrayJson = snapshot["boardArray"].toArray();
	mBoardProperties = new BoardProperties;
	mBoardProperties->maxAllowedUnits = boardProperties["maxAllowedUnits"].toInt();
	mBoardProperties->sizeX = boardProperties["sizeX"].toInt();
	mBoardProperties->sizeY = boardProperties["sizeY"].toInt();

	boardArray = new BoardCell * [mBoardProperties->sizeY];
	for (int i = 0; i < mBoardProperties->sizeY; i++) {
		BoardCell* tCellArray = new BoardCell[mBoardProperties->sizeX];
		boardArray[i] = tCellArray;
	}

	for (int i = 0; i < mBoardProperties->sizeY; i++) {
		for (int j = 0; j < mBoardProperties->sizeX; j++) {
			boardArray[i][j].x = j;
			boardArray[i][j].y = i;

			//terrain units
			qInfo() << boardArrayJson[i].toArray()[j].toObject();
			auto terrainUnit = boardArrayJson[i].toArray()[j].toObject()["terrainUnit"].toObject();

			if (terrainUnit["type"].toString() == "terrain") {
				auto type = terrainUnit["subtype"].toString();
				if (type == "grass")
					boardArray[i][j].terrainUnit = new Grass();
				else if (type == "snow")
					boardArray[i][j].terrainUnit = new Snow();
				else if (type == "river")
					boardArray[i][j].terrainUnit = new River();
			}

			auto unit = boardArrayJson[i].toArray()[j].toObject()["unit"].toObject();
			auto unitType = unit["type"].toString();

			if (unitType != "empty" && unitType != "playableUnit") {
				if (unitType == "neutral") {
					auto subtype = unit["subtype"].toString();
					if(subtype == "tree_log")
						boardArray[i][j].unit = new TreeLog();
					else if (subtype == "tree")
						boardArray[i][j].unit = new Tree();
					else if (subtype == "stone")
						boardArray[i][j].unit = new Stone();
					boardArray[i][j].isEmpty = false;
				}
				else if (unitType == "base") {
					//boardArray[i][j].unit = new PongoBaseBoardUnit(unit, this);
					boardArray[i][j].isEmpty = false;
				}
			}
		}
	}

}



