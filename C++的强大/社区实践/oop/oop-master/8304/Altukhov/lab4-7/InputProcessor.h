#pragma once
#include <string>
#include <vector>
#include "AttackCommand.h"
#include "MoveCommand.h"
#include "CreateCommand.h"
#include "BaseLogCommand.h"
#include "UnitInfoCommand.h"
#include "SaveCommand.h"
#include "LoadCommand.h"
#include "ProxyLog.h"
#include "GameState.h"
#include "FirstPlayerState.h"
#include "SecondPlayerState.h"

class Base;
class Field;

class InputProcessor {
	std::string input;
	Base* base;
	Base* base2;
	Field* field;
	ProxyLog* log;
	std::vector<std::string> split(const std::string& s, char delim);
	GameState* state;
	int curPlayer;
	bool checkArguments(std::vector<std::string>& args, int numberOfArgs, bool stringArg = false);
public:
	InputProcessor() {}
	InputProcessor(Base*& base, Base*& base2, Field*& field) :base(base), base2(base2), field(field), state(new FirstPlayerState(base, base2)), curPlayer(1) {}
	bool processString(std::string& input);//true - exit
	void attack(std::vector<std::string>& args);
	void move(std::vector<std::string>& args);
	void create(std::vector<std::string>& args);
	void baseLog();
	void unitInfo(std::vector<std::string>& args);
	void save(std::vector<std::string>& args);
	void load(std::vector<std::string>& args);
	void addLog(ProxyLog* log);
	void endOfTurn();
	void showField();
	void changeState(int playerNum);
	void onlyChangeState(int playerNum);
};

