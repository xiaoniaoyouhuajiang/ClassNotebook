#include "GameBoard.h"

GameBoard::GameBoard(int length, int width) {
	base1 = new Base(length/2 - 1, 0, 1);
	base2 = new Base(length/2 , width - 1, 2);
	observerManager = new ObserverManager();
	observerManager->addObserver(base1);
	observerManager->addObserver(base2);
	srand(0);
	this->length = length;
	this->width = width;
	maxUnitsOnBoard = length * width;
	board = new Cell**[length];
	for (int i = 0; i < length; i++) {
		board[i] = new Cell*[width];
	}
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			board[i][j] = new Cell();
		}
	}
	board[length / 2][0]->setBaseOnCell(base1);
	board[base2->getX()][base2->getY()]->setBaseOnCell(base2);
}


GameBoard::~GameBoard()
{
	delete[] board;
}

GameBoard::GameBoard(const GameBoard& other)
{
	this->length = other.length;
	this->width= other.width;
	this->maxUnitsOnBoard = other.maxUnitsOnBoard;
	this->unitsOnBoard = other.unitsOnBoard;
	this->observerManager = new ObserverManager(*other.observerManager);
	this->base1 = new Base(*other.base1);
	this->base2 = new Base(*other.base2);
	this->board = new Cell** [length];
	for (int i = 0; i < this->length; i++) {
		this->board[i] = new Cell* [this->width];
	}
	for (int i = 0; i < this->length; i++) {
		for (int j = 0; j < this->width; j++) {
			this->board[i][j] = new Cell(*other.board[i][j]);
		}
	}
}

GameBoard::GameBoard(GameBoard&& other) noexcept
{
	this->length = other.length;
	this->width = other.width;
	this->maxUnitsOnBoard = other.maxUnitsOnBoard;
	this->unitsOnBoard = other.unitsOnBoard;
	this->observerManager = new ObserverManager(*other.observerManager);
	this->base1 = new Base(*other.base1);
	this->base2 = new Base(*other.base2);
	this->board = new Cell **[length];
	for (int i = 0; i < this->length; i++) {
		this->board[i] = new Cell * [this->width];
	}
	for (int i = 0; i < this->length; i++) {
		for (int j = 0; j < this->width; j++) {
			this->board[i][j] = new Cell(*other.board[i][j]);
		}
	}
	this->observerManager = other.observerManager;
	other.board = nullptr;
	other.length = other.width = other.maxUnitsOnBoard = other.unitsOnBoard = 0;
}

int GameBoard::getLength()
{
	return length;
}


int GameBoard::getWidth()
{
	return width;
}

Cell*** GameBoard::getBoard()
{
	return this->board;
}

bool GameBoard::checkPossetion(std::pair<int, int> pos) 
{
	if (pos.first < 0 || pos.first > length - 1 || pos.second < 0 || pos.second > width - 1) {
		return false;
	}
	else return true;
}

bool GameBoard::createUnit(int baseNum, Units unitType, std::pair<int, int> pos, LoggerProxy* logger)
{
	Base* base;
	if (baseNum == 1)
		base = base1;
	else { 
		base = base2; 
		baseNum = 2;
	}
	if (board[pos.first][pos.second]->getEmptyOfCell() && checkPossetion(pos) && (unitsOnBoard + 1 < maxUnitsOnBoard) && base->checkCreating() && board[pos.first][pos.second]->getCellLandscape()->canGo())
	{
		logger->logInformation("Unit: " + IUnit::retrunUnitTypeString(unitType) + " was created from base " + std::to_string(baseNum) + " on possetion (" + std::to_string(pos.first) + ", " + std::to_string(pos.second) + ")");
		unitsOnBoard++;
		board[pos.first][pos.second]->setUnitOnCell(base->createUnit(unitType, pos));
		return true;
	}
	//else std::cout << board[pos.first][pos.second]->getEmptyOfCell() << " " << checkPossetion(pos) << " " << (unitsOnBoard + 1 < maxUnitsOnBoard) << " " << base->checkCreating() << " " << board[pos.first][pos.second]->getCellLandscape()->canGo() << std::endl;
	logger->logInformation("Can't create unit on possetion (" + std::to_string(pos.first) + ", " + std::to_string(pos.second) + ")");
	return false;
}

Base* GameBoard::getBase1()
{
	return base1;
}

Base* GameBoard::getBase2()
{
	return base2;
}

void GameBoard::addBase(Base* baseToAdd, std::pair<int, int> pos)
{
	if (baseNum + 1 < maxBaseNum)
	{
		baseNum++;
		board[pos.first][pos.second]->setBaseOnCell(baseToAdd);
	}
	observerManager->addObserver(baseToAdd);
}

void GameBoard::delBase(Base* base) 
{

	observerManager->removeObserver(base);
	board[base->getX()][base->getY()] -> delBaseOnCell();
}

void GameBoard::delUnit(std::pair<int, int> pos)
{
	if (checkPossetion(pos))
	{
		observerManager->notify(board[pos.first][pos.second]->killUnitOnCell(), Event::UNIT_KILL);
	}
}

bool GameBoard::moveUnit(std::pair<int, int> pos1, std::pair<int, int> pos2, LoggerProxy* logger)
{
	if (!checkPossetion(pos1) && !checkPossetion(pos2))
	{
		logger->logInformation("Possetion to move or unit possetion gone frome board");
		return false;
	}
	if (!(board[pos1.first][pos1.second]->getEmptyOfCell()) && board[pos2.first][pos2.second]->getEmptyOfCell())
	{
		logger->logInformation("Unit from possetinon: (" + std::to_string(pos1.first) + ", " + std::to_string(pos1.second) + ") was moved to (" + std::to_string(pos2.first) + ", " + std::to_string(pos2.second) + ")");
		board[pos2.first][pos2.second]->setUnitOnCell(board[pos1.first][pos1.second]->getUnitOnCell());
		board[pos1.first][pos1.second]->killUnitOnCell();
		return true;
	}
	logger->logInformation("No unit on possetinon: (" + std::to_string(pos1.first) + ", " + std::to_string(pos1.second) + ") or possetion (" + std::to_string(pos2.first) + ", " + std::to_string(pos2.second) + ") not empty");
	return false;
	
}

std::string GameBoard::getLine(int lineNum)
{
	std::string outString = "";
	for (int j = 0; j < width; j++) {
		outString += " ";
		outString += board[lineNum][j]->getCell();
		outString += " |";
	}
	return outString;
}


