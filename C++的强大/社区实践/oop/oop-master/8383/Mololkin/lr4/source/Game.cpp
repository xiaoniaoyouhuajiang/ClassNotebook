#include "Game.h"

Game::Game()
{
	int length;
	int width;
	std::cout << "Game starts!" << std::endl;
	std::cout << "Enter board length and width" << std::endl;
	std::cin >> length;
	std::cin >> width;
	while (length > 30 || length < 10 || width > 30 || width < 10) {
		std::cerr << "Error with board size" << std::endl;
		std::cout << "Enter board length and width" << std::endl;
		std::cin >> length;
		std::cin >> width;
	}
	board = new GameBoard(length, width);
	std::cout << "Choose logger type" << std::endl;
	std::cout << "1 - Terminal" << std::endl;
	std::cout << "2 - File" << std::endl;
	std::cout << "Another number - Without logger" << std::endl;
	int n;
	std::cin >> n;
	if (n == 1)
		logger = new LoggerProxy(LoggerType::TERMINAL);
	else if (n == 2)
		logger = new LoggerProxy(LoggerType::FILE);
	else logger = new LoggerProxy(LoggerType::EMPTYLOGGER);

	logger->logInformation("Game board was crated with length: " + std::to_string(length) + ", and width: " + std::to_string(width));
}

void printComands() {
	std::cout << "1 - Restart game" << std::endl;
	std::cout << "2 - Print board" << std::endl;
	std::cout << "3 - Move unit" << std::endl;
	std::cout << "4 - Print information about base" << std::endl;
	std::cout << "5 - Create unit from base" << std::endl;
	std::cout << "6 - Print information about unit" << std::endl;
	std::cout << "7 - Attack unit or base" << std::endl;
	std::cout << "8 - Change logger stream" << std::endl;
	std::cout << "All other numbs and symbols - Stop game" << std::endl;
}

void Game::startGame()
{
	Command* command;
	bool isGameGoing = true;
	logger->logInformation("Game was started!");
	while (isGameGoing) {
		printComands();
		int comandNum;
		std::cin >> comandNum;
		switch (comandNum)
		{
		case 1:
			command = new RestartCommand(&board, logger);
			break;
		case 2:
			command = new PrintBoardCommand(&board, logger);
			break;
		case 3:
			command = new MoveUnitCommand(&board, logger);
			break;
		case 4:
			command = new AboutBaseCommand(&board, logger);
			break;
		case 5:
			command = new CreateUnitFromBaseCommand(&board, logger);
			break;
		case 6:
			command = new AboutUnitCommand(&board, logger);
			break;
		case 7:
			command = new UnitAttackCommand(&board, logger);
			break;
		case 8:
			command = new ChangeLoggerCommand(logger);
			break;
		default:
			command = nullptr;
			isGameGoing = false;
			break;
		}
		if (!isGameGoing) { 
			break; 
		}
		if (command != nullptr && command->execute()) {
			std::cout << "The command was executed without problems" << std::endl;
		}
		else std::cout << "The command wasn't executed" << std::endl;
	}
	std::cout << "Game was finished" << std::endl;
	logger->logInformation("Game was finished");
	logger->stopLogging();
	logger->~LoggerProxy();

}

PrintBoardCommand::PrintBoardCommand(GameBoard** board, LoggerProxy* logger)
{
	this -> board = board;
	this->logger = logger;
}

bool PrintBoardCommand::execute()
{
	for (int i = 0; i < (*board)->getLength(); i++) {
		if (i < 10) std::cout << i << " |";
		else std::cout << i << "|";
		std::cout << (*board)->getLine(i);
		std::cout << std::endl;
	}
	std::cout << "  ";
	for (int i = 0; i < (*board)->getWidth(); i++)
	{
		if (i + 1 < 10) std::cout << "   " << i << "    ";
		else if (i == 9) std::cout << "  " << i;
		else std::cout << "      " << i;
	}
	std::cout << std::endl;
	std::cout << "---";
	for (int i = 0; i < (*board)->getWidth(); i++)
	{
		std::cout << "----";
	}
	std::cout << std::endl;
	logger->logInformation("Game board was print");
	return true;
}


RestartCommand::RestartCommand(GameBoard** board, LoggerProxy* logger)
{
	this->board = board;
	this->logger = logger;
}

bool RestartCommand::execute()
{
	int length;
	int width;
	std::cout << "Game starts!" << std::endl;
	std::cout << "Enter board length and width" << std::endl;
	std::cin >> length;
	std::cin >> width;
	while (length > 30 || length < 10 || width > 30 || width < 10) {
		std::cerr << "Error with board size" << std::endl;
		std::cout << "Enter board length and width" << std::endl;
		std::cin >> length;
		std::cin >> width;
	}
	*board = new GameBoard(length, width);
	logger->logInformation("Game was restarted");
	return true;
}

MoveUnitCommand::MoveUnitCommand(GameBoard** board, LoggerProxy* logger)
{
	this->board = board;
	this->logger = logger;
}

bool MoveUnitCommand::execute()
{
	std::cout << "Enter coordinates of unit, and coordinates where to move unit" << std::endl;
	int coordX1, coordY1, coordX2, coordY2;
	std::cin >> coordY1 >> coordX1 >> coordY2 >> coordX2;
	bool result = (*board)->moveUnit(std::pair<int, int>(coordX1, coordY1), std::pair<int, int>(coordX2, coordY2), logger);
	return result;
}

AboutBaseCommand::AboutBaseCommand(GameBoard** board, LoggerProxy* logger)
{
	this->board = board;
	this->logger = logger;
}

bool AboutBaseCommand::execute()
{
	std::cout << "Enter base number 1 or 2" << std::endl;
	int baseNumber;
	std::cin >> baseNumber;
	Base* base;
	if(baseNumber == 1)
		base = (*board)->getBase1();
	else if(baseNumber == 2)
		base = (*board)->getBase2();
	else return false;
	std::cout << "Base information:" << std::endl;
	std::cout << "Team: " << base->getBaseNum() << std::endl;
	std::cout << "Posittion: (" << base->getX() << "," << base->getY() << ")" << std::endl;
	std::cout << "Health: " << base->getHealth() << std::endl;
	std::cout << "Number units from base: " << base->getNumUnitsFromBase() << std::endl;
	logger->logInformation("Information about base" + std::to_string(baseNumber) + " was printed");
	return true;
}

AboutUnitCommand::AboutUnitCommand(GameBoard** board, LoggerProxy* logger)
{
	this->board = board;
	this->logger = logger;
}

bool AboutUnitCommand::execute()
{
	std::cout << "Enter coordinates of unit" << std::endl;
	int coordX, coordY;
	std::cin >> coordY >> coordX;
	IUnit* unit = (*board) -> getBoard()[coordX][coordY] -> getUnitOnCell() ;
	if (unit == nullptr) return false;
	std::cout << "Team: " << unit->getTeam() << std::endl;
	std::cout << "Health: " << unit->getHealth() << std::endl;
	std::cout << "Armour: " << unit->getArmour() << std::endl;
	std::cout << "Attack: " << unit->getAttack() << std::endl;
	logger->logInformation("Information about unit on possetion (" + std::to_string(coordY) +", " +std::to_string(coordX) + ") was printed");
	return true;
}

CreateUnitFromBaseCommand::CreateUnitFromBaseCommand(GameBoard** board, LoggerProxy* logger)
{
	this->board = board;
	this->logger = logger;
}

bool CreateUnitFromBaseCommand::execute()
{
	std::cout << "Enter base number 1 or 2" << std::endl;
	int baseNumber;
	std::cin >> baseNumber;
	if (!(baseNumber == 1 || baseNumber == 2)) return false;
	std::cout << "Choose unit type" << std::endl;
	std::cout << "1 - Spearman" << std::endl;
	std::cout << "2 - Swordsman" << std::endl;
	std::cout << "3 - Archer" << std::endl;
	std::cout << "4 - Ballista" << std::endl;
	std::cout << "5 - Crossbowman" << std::endl;
	std::cout << "6 - Catapult" << std::endl;
	int unitNumber;
	std::cin >> unitNumber;
	if (unitNumber < 1 && unitNumber > 6) return false;
	Units unitType = static_cast<Units>(unitNumber);
	std::cout << "Enter unit possition" << std::endl;
	int coordX, coordY;
	std::cin >> coordY >> coordX;
	return (*board)->createUnit(baseNumber, unitType, std::pair<int, int>(coordX, coordY), logger);
}

UnitAttackCommand::UnitAttackCommand(GameBoard** board, LoggerProxy* logger)
{
	this->board = board;
	this->logger = logger;
}

bool UnitAttackCommand::execute()
{
	Mediator* mediator = new AttackMediator();
	std::cout << "Enter coordinates attacker and attacked";
	int coordX1, coordY1, coordX2, coordY2;
	std::cin >> coordY1 >> coordX1 >> coordY2 >> coordX2;
	IUnit* attacker;
	if (!(*board)->getBoard()[coordX1][coordY1]->getEmptyOfCell() && (*board)->getBoard()[coordX1][coordY1]->getIsUnitOnCell()) {
		attacker = (*board)->getBoard()[coordX1][coordY1]->getUnitOnCell();
	}
	else {
		logger->logInformation("No attacker on possetion: (" + std::to_string(coordY1) + ", " + std::to_string(coordX1) + ")");
		return false;
	}
	if (!(*board)->getBoard()[coordX2][coordY2]->getEmptyOfCell()) {
		if ((*board)->getBoard()[coordX2][coordY2]->getIsUnitOnCell()) {
			logger->logInformation("Unit on possetion: (" + std::to_string(coordY1) + ", " + std::to_string(coordX1) + ") attacked unit on possetion: (" + std::to_string(coordY2) + ", " + std::to_string(coordX2) + ")");
			logger->logUnitAttacked((*board)->getBoard()[coordX2][coordY2]->getUnitOnCell());
			mediator->attackUnit(attacker->getAttack(), (*board)->getBoard()[coordX2][coordY2]->getUnitOnCell());
		}
		else {
			logger->logInformation("Unit on possetion: (" + std::to_string(coordY1) + ", " + std::to_string(coordX1) + ") attacked base " + std::to_string((*board)->getBoard()[coordX2][coordY2]->getBaseOnCell()->getBaseNum()));
			mediator->attackBase(attacker->getAttack(), (*board)->getBoard()[coordX2][coordY2]->getBaseOnCell());
			logger->logBaseAttacked((*board)->getBoard()[coordX2][coordY2]->getBaseOnCell());
		}
		return true;
	}
	else return false;
}

bool ChangeLoggerCommand::execute()
{
	std::cout << "Choose logger type" << std::endl;
	std::cout << "1 - Terminal" << std::endl;
	std::cout << "2 - File" << std::endl;
	std::cout << "Another number - Without logger" << std::endl;
	int n;
	std::cin >> n;
	LoggerType type;
	if (n == 1) type = LoggerType::TERMINAL;
	else if (n == 2) type = LoggerType::FILE;
	else type =  LoggerType::EMPTYLOGGER;
	logger->stopLogging();
	logger->changeLogger(type);

	/*logger = new LoggerProxy(type);*/
	return true;
}
