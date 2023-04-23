#pragma once
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Board.h"
#include "ActionDispatcher.h"
#include "GameRulesClassic.h"
#include "GameRulesRandom.h"

class UItoBackendConnector;

class Game
{
public:
	static Game* getInstance();
	void initGUI(int argc, char* argv[]);
	void initGame(int rulesetType, std::vector<std::string> users, int sizeX, int sizeY, int maxAllowedUnits);
	//void initGameCustom();
	Board* getBoard();
	int Start();
	void _debug_demo();
	void playerAction(Board::BoardCell fromCell, Board::BoardCell toCell, int actionID = -1);
	User* getCurrentUser();
	BoardUnit::ActionMeta checkPlayerAction(Board::BoardCell fromCell, Board::BoardCell toCell, int actionID = -1);
	std::vector<ActionDispatcher::Action>* getCellsToUpdate();
	bool save(std::string fileName);
	bool load(std::string fileName);
	~Game();
protected:
	void initBoard(int sizeX, int sizeY, int maxAllowedUnits);

	std::vector<ActionDispatcher::Action>* changedCells = nullptr;
	static Game* mInstance;
	Board* mGameBoard = nullptr;
	ActionDispatcher* mActionDispatcher = nullptr;
	std::vector<User*> _users;
	GameRules* _rules = nullptr;
	int currentTurn = 0;

	QGuiApplication* _qApp;
	QQmlApplicationEngine* _qEngine;
	UItoBackendConnector* _connector;
};

