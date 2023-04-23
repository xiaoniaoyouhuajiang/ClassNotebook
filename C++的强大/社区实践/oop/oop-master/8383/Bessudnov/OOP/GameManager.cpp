#include "pch.h"
#include <fstream>
#include <algorithm> 
#include <vector>
#include "GameManager.h"
#include "GameUtilities.h"
#include "GameVisualiser.h"
#include "GameField.h"
#include "GameUnits.h"
#include "NeutralObject.h"
#include "PlayerInput.h"
#include "GameBases.h"
#include "Logger.h"
#include "GameLoaderSaver.h"
#include "GameUnits.h"
#include "FieldBlock.h"


GameManager::GameManager(GameField *field, NeutralObjectContainer *nObjects, GameVisualiser *visualiser) : 
	gameField(field), objectsContainer(nObjects), visualiser(visualiser), isActive(false) {
	inputManager = new PlayerInput;
	loggerProxy = new LoggerProxy;

	baseContainer = new GameBasesContainer(gameField);
	gameUnits = new GameUnits(gameField->getFieldBorders(), gameField, baseContainer);

	actionManager = new ActionManager(baseContainer, gameUnits, loggerProxy, gameField, this);

}


GameManager::~GameManager() {
	delete inputManager;
	delete gameField;
	delete gameUnits;
	delete visualiser;
	delete objectsContainer;
	delete baseContainer;
}

void GameManager::loadGame(GameManagerSnapshot *gameSnaphot) {
	baseContainer->bases.clear();
	gameUnits->units.clear();
	for (auto &baseInfo : *gameSnaphot->getBasesInfo()) {
		switch (baseInfo.type) {
		case GameBaseTypes::Zero:
			baseContainer->bases.push_back(new DefaultBase(gameUnits));
			break;
		case GameBaseTypes::One:
			baseContainer->bases.push_back(new OneBase(gameUnits));
			break;
		case GameBaseTypes::Two:
			baseContainer->bases.push_back(new TwoBase(gameUnits));
			break;
		case GameBaseTypes::Three:
			baseContainer->bases.push_back(new ThreeBase(gameUnits));
			break;
		case GameBaseTypes::Four:
			baseContainer->bases.push_back(new FourBase(gameUnits));
			break;
		}

		baseContainer->bases.back()->location = baseInfo.loc;
		baseContainer->bases.back()->dew.setVal(baseInfo.dew);
		baseContainer->bases.back()->ligth.setVal(baseInfo.ligth);
		baseContainer->bases.back()->isActive = baseInfo.isActive;
	}

	for (auto &unitInfo : *gameSnaphot->getUnitsInfo()) {
		baseContainer->currentBaseIndex = unitInfo.baseIndex;
		baseContainer->spawnUnit('1' + unitInfo.spawnOrder);
		gameField->getBlockAtLocation(gameUnits->units.back()->unitProps.location)->setUnit(nullptr);
		gameUnits->units.back()->unitProps = unitInfo.props;
	}

	isActive = gameSnaphot->getIsActive();

	for (auto unit : gameUnits->units) {
		gameField->getBlockAtLocation(unit->unitProps.location)->setUnit(unit);
	}

	for (auto base : baseContainer->bases) {
		gameField->getBlockAtLocation(base->location)->setBase(base);
	}
}

int GameManager::playerAction() {
	char messageCommand;
	inputManager->readInput(messageCommand);

	int actionResult = actionManager->action(messageCommand);


	return actionResult;
}

void GameManager::neutralObjectExec() {
	if (*objectsContainer == *gameUnits) {
		objectsContainer->useObject(*gameUnits);
	}
}

void GameManager::pickBases(float position) {
	baseContainer->spawnDefaultBase(gameUnits, position);
	for (int i = 0; i < 2; i++) {
		switch (std::stoi(inputManager->readString("Pick base: "))) {
		case GameBaseTypes::One:
			baseContainer->bases.push_back(new OneBase(gameUnits));
			break;
		case GameBaseTypes::Two:
			baseContainer->bases.push_back(new TwoBase(gameUnits));
			break;
		case GameBaseTypes::Three:
			baseContainer->bases.push_back(new ThreeBase(gameUnits));
			break;
		case GameBaseTypes::Four:
			baseContainer->bases.push_back(new FourBase(gameUnits));
			break;
		} 

		Vector2D baseLoc(i * (gameField->fieldProps.dimensions.x - 1), (gameField->fieldProps.dimensions.x - 1) * position);
		
		baseContainer->bases.back()->location = baseLoc;

		gameField->getBlockAtLocation(baseLoc)->setBase(baseContainer->bases.back());
	}
}

GameManager::GameManager(const GameManager * gameManager) {
}

void UnitCommander::unitAttack() {
	Vector2D *attackDirection = new Vector2D(0, 0);
	command = new UnitAttackDirectionCommand(playerInput, attackDirection);
	command->execute();
	command = new ActionUnitCommand(unitsContainer, *attackDirection);
	command->execute();
	output("ATTACK");
}

UnitCommander::UnitCommander(GameUnits * unitsContainer, LoggerProxy * loggerProxy) :
	unitsContainer(unitsContainer), Commander(loggerProxy) {
	playerInput = new PlayerInput;
}

UnitCommander::~UnitCommander() {
	delete unitsContainer;
}

int UnitCommander::doAction(char action) {
	switch (action) {
	case NEXT_UNIT_COMMAND:
		command = new NextUnitCommand(unitsContainer, 1);
		command->execute();
		output("NEXT UNIT");
		return 1;
	case PREV_UNIT_COMMAND:
		command = new NextUnitCommand(unitsContainer, 0);
		command->execute();
		output("PREV UNIT");
		return 1;
	case MOVE_UP_COMMAND:
		command = new MoveUnitCommand(unitsContainer, Vector2D(0, -1));
		command->execute();
		output("MOVE UP");
		return 2;
	case MOVE_DAWN_COMMAND:
		command = new MoveUnitCommand(unitsContainer, Vector2D(0, 1));
		command->execute();
		output("MOVE DAWN");
		return 2;
	case MOVE_LEFT_COMMAND:
		command = new MoveUnitCommand(unitsContainer, Vector2D(-1, 0));
		command->execute();
		output("MOVE LEFT");
		return 2;
	case MOVE_RIGTH_COMMAND:
		command = new MoveUnitCommand(unitsContainer, Vector2D(1, 0));
		command->execute();
		output("MOVE RIGTH");
		break;
	case ATTACK_COMMAND:
		unitAttack();
		return 2;
	case SACRAFICE_COMMAND:
		command = new UnitSacraficeCommand(unitsContainer);
		command->execute();
		output("UNIT SCRAFICED");
		return 2;
	default:
		return 0;
	}

	return 1;
}

BaseCommander::~BaseCommander() {
	delete baseContainer;
}

int BaseCommander::doAction(char action) {
	switch (action) {
	case NEXT_BASE_COMMAND:
		command = new NextBaseCommand(baseContainer, 1);
		command->execute();
		output("NEXT BASE");
		return 1;
	case PREV_BASE_COMMAND:
		command = new NextBaseCommand(baseContainer, 0);
		command->execute();
		output("PREV BASE");
		return 1;
	case SPAWN_COLLECTOR:
		command = new SpawnUnitCommand(baseContainer, SPAWN_COLLECTOR);
		command->execute();
		output("SPAWN COLLECTOR");
		return 2;
	case SPAWN_SPRINKLER:
		command = new SpawnUnitCommand(baseContainer, SPAWN_SPRINKLER);
		command->execute();
		output("SPAWN SPRINKLER");
		return 2;
	case SPAWN_UNIT01:
		command = new SpawnUnitCommand(baseContainer, SPAWN_UNIT01);
		command->execute();
		output("SPAWN UNIT01");
		return 2;
	case SPAWN_UNIT02:
		command = new SpawnUnitCommand(baseContainer, SPAWN_UNIT02);
		command->execute();
		output("SPAWN UNIT02");
		return 2;
	case SPAWN_UNIT03:
		command = new SpawnUnitCommand(baseContainer, SPAWN_UNIT03);
		command->execute();
		output("SPAWN UNIT03");
		return 2;
	default:
		return 0;
	}

	return 1;
}

ActionManager::~ActionManager() {
	delete baseCommander;
	delete unitCommander;
	delete gameFlowCommander;
}

int ActionManager::action(char action) {
	int result;
	result = baseCommander->doAction(action);
	if (result) {
		return result;
	}

	result = unitCommander->doAction(action);
	if (result) {
		return result;
	}

	result = gameFlowCommander->doAction(action);
	if (result) {
		return result;
	}

	return 0;
}

GameFlowCommander::GameFlowCommander(LoggerProxy *loggerProxy, GameManager *manager) : Commander(loggerProxy) {
}

int GameFlowCommander::doAction(char action) {
	switch (action) {
	case EXIT_COMMAND:
		output("EXIT");
		return -1;
	case SAVE_COMMAND:
		output("SAVING GAME");
		return -2;
	case LOAD_COMMAND:
		output("LOADING GAME");
		return -3;
	case NEW_GAME:
		output("NEW GAME");
		return -4;
	default:
		output("WRONG");
		return 0;
	}

	return -1;
}

void Commander::output(std::string message) {
	loggerProxy->logEvent(new LogEntry(message));
}

std::ofstream &operator<<(std::ofstream &os, GameManager::GameManagerSnapshot &snapshot) {
	os << snapshot.isActive << std::endl;
	os << snapshot.basesInfo.size() << std::endl;
	for (auto &base : snapshot.basesInfo) {
		os << base.dew << " ";
		os << base.ligth << " ";
		os << base.loc << " ";
		os << base.isActive << " ";
		os << base.type << std::endl;
	}
	os << snapshot.unitsInfo.size() << std::endl;
	for (auto &unit : snapshot.unitsInfo) {
		os << unit.baseIndex << " ";
		os << unit.spawnOrder << " ";
		os << unit.props << std::endl;
	}

	return os;
}

std::ifstream &operator>>(std::ifstream &is, GameManager::GameManagerSnapshot &snapshot) {
	is >> snapshot.isActive;
	int basesCount;
	is >> basesCount;
	snapshot.basesInfo.resize(basesCount);
	for (auto &base : snapshot.basesInfo) {
		is >> base.dew;
		is >> base.ligth;
		is >> base.loc;
		is >> base.isActive;
		is >> base.type;
	}
	int unitsCount;

	is >> unitsCount;
	snapshot.unitsInfo.resize(unitsCount);
	for (auto &unit : snapshot.unitsInfo) {
		is >> unit.baseIndex;
		is >> unit.spawnOrder;
		is >> unit.props;
	}
	return is;
}

GameManager::GameManagerSnapshot::GameManagerSnapshot(GameBasesContainer *bases, bool isActive) : isActive(isActive) {
	basesInfo.clear();
	unitsInfo.clear();
	for (auto &base : bases->bases) {
		basesInfo.push_back(BaseSave(base->type, base->location, base->dew.getVal(), base->ligth.getVal(), base->isActive));
		for (int i = 0; i < base->baseUnits.size(); i++) {
			for (int j = 0; j < base->baseUnits[i]->units.size(); j++) {
				if (base->baseUnits[i]->units[j]) {
					UnitParent *tmp;
					tmp = base->baseUnits[i]->units[j];
					unitsInfo.push_back(UnitSave(i * 2 + j, basesInfo.size() - 1, tmp));
				}
			}
		}
	}
}

UnitSave::UnitSave(int order, int baseIndex, UnitParent *unit) : spawnOrder(order), baseIndex(baseIndex) {
	props = unit->unitProps;
}

