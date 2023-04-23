#include "pch.h"
#include "GameManager.h"
#include "GameVisualiser.h"
#include "GameUtilities.h"
#include "NeutralObject.h"
#include "GameBases.h"
#include "GameField.h"
#include "GameUnits.h"



GameVisualiser::GameVisualiser(GameField *field, NeutralObjectContainer *objCon) : field(field), nObjects(objCon) {
	blueTeam = nullptr;
	redTeam = nullptr;
	console = GetStdHandle(STD_OUTPUT_HANDLE);
	initCommands();
}


GameVisualiser::~GameVisualiser() {

}

void GameVisualiser::update() {
	system("cls");
	for (int i = 0; i < field->fieldProps.dimensions.y; i++) {
		for (int j = 0; j < field->fieldProps.dimensions.x; j++) {
			/*drawResult = drawObj(Vector2D(j, i));
			if (redTeam) {
				drawResult = drawResult || drawUnit(redTeam, Vector2D(j, i)) || drawBase(redTeam, Vector2D(j, i));
			}

			if (blueTeam) {
				drawResult = drawResult || drawUnit(blueTeam, Vector2D(j, i)) || drawBase(blueTeam, Vector2D(j, i));
			}

			if (!drawResult) {
				SetConsoleTextAttribute(console, field->fieldProps.blocks[j][i]->blockType);
				std::cout << field->fieldProps.blocks[j][i]->blockType;
			}*/

			UnitParent *unitOnBlock;
			unitOnBlock = field->getBlockAtLocation(Vector2D(j, i))->getUnit();
			if (unitOnBlock) {
				SetConsoleTextAttribute(console, 6);
				std::cout << unitOnBlock->unitProps.type;
			}

			NeutralObject *objectOnBlock;
			objectOnBlock = field->getBlockAtLocation(Vector2D(j, i))->getObject();
			if (objectOnBlock) {
				SetConsoleTextAttribute(console, 5 | BACKGROUND_INTENSITY);
				std::cout << objectOnBlock->type;
			}

			GameBase *baseOnBlock;
			baseOnBlock = field->getBlockAtLocation(Vector2D(j, i))->getBase();
			if (baseOnBlock) {
				SetConsoleTextAttribute(console, 12);
				std::cout << baseOnBlock->type;
			}

			if (!baseOnBlock && !objectOnBlock && !unitOnBlock) {
				SetConsoleTextAttribute(console, field->fieldProps.blocks[j][i]->blockType);
				std::cout << field->fieldProps.blocks[j][i]->blockType;
			}

			SetConsoleTextAttribute(console, 0);
			std::cout << " ";
		}
		std::cout << std::endl;
	}
	if (blueTeam) {
		if (blueTeam->isActive) {
			SetConsoleTextAttribute(console, 1);
			std::cout << "Current Team - BLUE" << std::endl;
		}
		printBases(blueTeam->baseContainer);
		printUnits(blueTeam->gameUnits);
	}

	if (redTeam) {
		if (redTeam->isActive) {
			SetConsoleTextAttribute(console, 1);
			std::cout << "Current Team - RED" << std::endl;
		}
		printBases(redTeam->baseContainer);
		printUnits(redTeam->gameUnits);
	}

	
	printCommands();
}

void GameVisualiser::printUnits(GameUnits *units) {
	SetConsoleTextAttribute(console, 6);
	std::cout << "UNITS" << std::endl;
	std::cout << std::endl;
	for (auto &unit : units->units) {
		if (unit->unitProps.isActive) {
			std::cout << ">> ";
		}
		std::cout << unit->unitProps.type << " (";
		std::cout << unit->unitProps.location.x << ",";
		std::cout << unit->unitProps.location.y << ") ";
		std::cout << "dew: " << unit->unitProps.dew.parameterValueCurrent << " ";
		std::cout << "ligth: " << unit->unitProps.ligth.parameterValueCurrent << " ";
		std::cout << "moves: " << unit->unitProps.moves.parameterValueCurrent << " ";
		std::cout << "damage: " << unit->unitProps.damage.parameterValueCurrent << " ";
		std::cout << "sugar: " << unit->unitProps.sugar.parameterValueCurrent << std::endl;
	}
	std::cout << std::endl;
}

void GameVisualiser::printBases(GameBasesContainer *bases) {
	SetConsoleTextAttribute(console, 12);
	std::cout << std::endl;
	std::cout << "BASES" << std::endl;
	for (auto &base : bases->bases) {
		if (base->isActive) {
			std::cout << ">> ";
		}
		std::cout << "Type: " << base->type;
		std::cout << " Dew: " << base->dew << std::endl;
		for (auto &units : base->baseUnits) {
			for (auto &unit : units->units) {
				if (unit != nullptr) {
					std::cout << "	";
					if (unit->unitProps.isActive) {
						std::cout << "> ";
					}
					std::cout << "Unit type: " << unit->unitProps.type;
					std::cout << std::endl;
				}
			}
		}
	}
}

void GameVisualiser::printMessage(std::string message, int delay) {
	SetConsoleTextAttribute(console, 7);
	std::cout << message << std::endl;
	Sleep(delay);
}

void GameVisualiser::printCommands() {
	std::cout << "COMMANDS" << std::endl;

	for (commandsIt = commands.begin(); commandsIt != commands.end(); commandsIt++) {
		std::cout << commandsIt->first << "---" << commandsIt->second << std::endl;
	}
}

void GameVisualiser::initCommands() {
	std::ifstream ifs;
	ifs.open("controls.txt", std::ifstream::in);

	std::string inputS;
	char inputC;
	while (ifs >> inputS && ifs >> inputC) {
		commands[inputS] = inputC;
	}

	ifs.close();
}

bool GameVisualiser::drawObj(Vector2D loc) {
	NeutralObject *curObj;
	curObj = nullptr;

	curObj = nObjects->getObjectAtLocation(loc);
	if (curObj != nullptr) {
		SetConsoleTextAttribute(console, 5 | BACKGROUND_INTENSITY);
		std::cout << curObj->type;
		return true;
	}
	return false;
}

bool GameVisualiser::drawUnit(GameManager *team, Vector2D loc) {
	UnitParent *curUnit;
	curUnit = nullptr;

	curUnit = team->gameUnits->getUnit(loc);
	if (curUnit != nullptr) {
		SetConsoleTextAttribute(console, 6);
		std::cout << curUnit->unitProps.type;
		return true;
	}
	return false;
}

bool GameVisualiser::drawBase(GameManager *team, Vector2D loc) {
	GameBase *curBase;
	curBase = nullptr;

	curBase = team->baseContainer->getBaseAtLocation(loc);
	if (curBase != nullptr) {
		SetConsoleTextAttribute(console, 12);
		std::cout << curBase->type;
		return true;
	}
	return false;
}
