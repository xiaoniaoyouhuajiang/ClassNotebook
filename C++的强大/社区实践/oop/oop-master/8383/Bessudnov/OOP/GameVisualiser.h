#pragma once
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <map>

class GameField;
class GameUnits;
class NeutralObjectContainer;
class GameBasesContainer;
class Vector2D;
class GameManager;

class GameVisualiser {
public:
	GameVisualiser(GameField *field, NeutralObjectContainer *objCon);
	~GameVisualiser();

	void update();
	void printUnits(GameUnits *units);
	void printBases(GameBasesContainer *bases);
	void printMessage(std::string message, int delay);
	void printCommands();
	void setBlueTeam(GameManager *team) {
		blueTeam = team;
	}
	void setRedTeam(GameManager *team) {
		redTeam = team;
	}
private:
	GameField *field;
	NeutralObjectContainer *nObjects;
	GameManager *blueTeam;
	GameManager *redTeam;

	HANDLE console;
	std::map<std::string, char> commands;
	std::map<std::string, char>::iterator commandsIt;

	void initCommands();

	bool drawObj(Vector2D loc);
	bool drawUnit(GameManager *team, Vector2D loc);
	bool drawBase(GameManager *team, Vector2D loc);
};

