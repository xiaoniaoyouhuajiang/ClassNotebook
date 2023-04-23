#pragma once
#include <string>
#include <vector>
#include "AttackCommand.h"
#include "MoveCommand.h"
#include "CreateCommand.h"
#include "BaseLogCommand.h"
#include "UnitInfoCommand.h"


class Base;

class InputProcessor {
	std::string input;
	Base* base;

	std::vector<std::string> split(const std::string& s, char delim);
	bool checkArguments(std::vector<std::string>& args, int numberOfArgs);
public:
	InputProcessor(Base*& base) :base(base) {}
	bool processString(std::string& input);//true - exit
	void attack(std::vector<std::string>& args);
	void move(std::vector<std::string>& args);
	void create(std::vector<std::string>& args);
	void baseLog();
	void unitInfo(std::vector<std::string>& args);
};

