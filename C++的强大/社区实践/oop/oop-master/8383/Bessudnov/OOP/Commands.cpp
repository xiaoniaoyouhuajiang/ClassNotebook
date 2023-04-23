#include "pch.h"
#include "Commands.h"
#include "GameBases.h"
#include "GameUnits.h"
#include "PlayerInput.h"

MoveUnitCommand::~MoveUnitCommand() {
	delete unitsContainer;
}

void MoveUnitCommand::execute() {
	unitsContainer->moveUnit(direction);
}

NextUnitCommand::~NextUnitCommand() {
	delete unitsContainer;
}

void NextUnitCommand::execute() {
	unitsContainer->switchUnit(isNext);
}

NextBaseCommand::~NextBaseCommand() {
	delete baseContainer;
}

void NextBaseCommand::execute() {
	baseContainer->switchBase(isNext);
}

SpawnUnitCommand::~SpawnUnitCommand() {
	delete baseContainer;
}

void SpawnUnitCommand::execute() {
	baseContainer->spawnUnit(type);
}

ActionUnitCommand::~ActionUnitCommand() {
	delete unitsContainer;
}

void ActionUnitCommand::execute() {
	unitsContainer->units[unitsContainer->currentUnitIndex]->attack(direction);
}

BaseCommands::~BaseCommands() {
	delete baseContainer;
}

UnitCommands::~UnitCommands() {
	delete unitsContainer;
}

void UnitAttackDirectionCommand::execute() {
	char direction;
	input->readInput(direction);
	switch (direction) {
	case 'w':
		dir->x = 0;
		dir->y = -1;
		break;
	case 's':
		dir->x = 0;
		dir->y = 1;
		break;
	case 'a':
		dir->x = -1;
		dir->y = 0;
		break;
	case 'd':
		dir->x = 1;
		dir->y = 0;
		break;
	default:
		dir = new Vector2D(0, -1);
	}
}

void UnitSacraficeCommand::execute() {
	unitsContainer->units[unitsContainer->currentUnitIndex]->sacrafice();
}
