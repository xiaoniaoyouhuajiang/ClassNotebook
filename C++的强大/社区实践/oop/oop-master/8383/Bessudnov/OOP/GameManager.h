#pragma once
#include <iostream>
#include <utility>
#include "Commands.h"
#include <vector>
#include "UnitParent.h"

#define WAIT_TIME 1000

class GameManager;
class GameUnits;
class PlayerInput;
class GameField;
class GameVisualiser;
class Vector2D;
class NeutralObjectContainer;
class GameBasesContainer;
class LoggerProxy;
class GameLoaderSaver;
class PlayerInput;
class UnitParent;

struct UnitProperties;

class Commander {
private:
	LoggerProxy *loggerProxy;
protected:
	void output(std::string message);
public:
	Commander(LoggerProxy *loggerProxy) : loggerProxy(loggerProxy) {}

	virtual ~Commander() {
		delete loggerProxy;
	}

	virtual int doAction(char action) = 0;
};

class UnitCommander : public Commander {
private:
	GameUnits *unitsContainer;
	PlayerInput *playerInput;

	UnitCommands *command;

	void unitAttack();

public:
	UnitCommander(GameUnits *unitsContainer, LoggerProxy *loggerProxy);

	~UnitCommander();

	int doAction(char action);
};

class BaseCommander : public Commander {
private:
	GameBasesContainer *baseContainer;
	
	BaseCommands *command;

public:
	BaseCommander(GameBasesContainer *baseContainer, LoggerProxy *loggerProxy) :
		baseContainer(baseContainer), Commander(loggerProxy) {}

	~BaseCommander();

	int doAction(char action);
};

class GameFlowCommander : public Commander {
public:
	GameFlowCommander(LoggerProxy *loggerProxy, GameManager *manager);

	int doAction(char action);
};

class ActionManager {
private:
	BaseCommander *baseCommander;
	UnitCommander *unitCommander;
	GameFlowCommander *gameFlowCommander;
	GameField *gameField;
public:
	ActionManager(GameBasesContainer *baseContainer, GameUnits *unitsContainer,
		LoggerProxy *loggerProxy, GameField *field, GameManager *manager)
		: gameField(field) {
		baseCommander = new BaseCommander(baseContainer, loggerProxy);
		unitCommander = new UnitCommander(unitsContainer, loggerProxy);
		gameFlowCommander = new GameFlowCommander(loggerProxy, manager);
	}

	~ActionManager();

	int action(char action);
};

struct BaseSave {
	int type;
	Vector2D loc;
	int dew;
	int ligth;
	bool isActive;
	BaseSave() = default;
	BaseSave(int type, Vector2D loc, int dew, int ligth, bool isActive) : type(type), loc(loc), dew(dew), ligth(ligth), isActive(isActive) {
	}
};

struct UnitSave {
	int spawnOrder;
	int baseIndex;
	UnitProperties props;
	UnitSave() = default;
	UnitSave(int order, int baseIndex, UnitParent *unit);
};

class GameManager {
private:
	void neutralObjectExec();

public:
	bool isActive;
	int playerAction();
	void pickBases(float position);

	GameManager(const GameManager *gameManager);

	GameManager(GameField *field, NeutralObjectContainer *nObjects, GameVisualiser *visualiser);
	~GameManager();
	NeutralObjectContainer *objectsContainer;
	GameUnits *gameUnits;
	PlayerInput *inputManager;
	GameField *gameField;
	GameVisualiser *visualiser;
	GameBasesContainer *baseContainer;
	ActionManager *actionManager;
	LoggerProxy *loggerProxy;

	class GameManagerSnapshot {
	private:
		bool isActive;
		std::vector<BaseSave> basesInfo;
		std::vector<UnitSave> unitsInfo;
	public:
		GameManagerSnapshot(GameBasesContainer *bases, bool isActive);
		GameManagerSnapshot() = default;

		
		std::vector<BaseSave> *getBasesInfo() {
			return &basesInfo;
		};

		std::vector<UnitSave> *getUnitsInfo() {
			return &unitsInfo;
		};

		bool getIsActive() {
			return isActive;
		};


		friend std::ofstream &operator<<(std::ofstream &os, GameManagerSnapshot &snapshot);
		friend std::ifstream &operator>>(std::ifstream &is, GameManagerSnapshot &snapshot);
	};

	GameManagerSnapshot *saveGame() {
		return new GameManagerSnapshot(baseContainer, isActive);
	}

	void loadGame(GameManagerSnapshot *gameSnaphot);
};


