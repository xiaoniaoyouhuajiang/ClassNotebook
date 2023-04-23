//#pragma once
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <iomanip>
//#include "Warrior.h"
//#include "Orcs.h"
//#include "Men.h"
//#include "Elfs.h"
#include "../Field/Field.h"
#include "../Field/Iterator.h"
#include "../Base/Base.h"
#include "Command.h"
//#include "Landscape.h"
//#include "NeutralObject.h"
#include "../Logging/LoggerProxy.h"
#include "../Logging/LoggerFormat.h"
#include "../Logging/LoggingTerminal.h"
#include "../Logging/LoggingFile.h"
#include "../Logging/NoLogging.h"
#include "../CommandMemento.h"
#include "../Game/States/StateContext.h"
//#include "Rules.h"
#include "../Game/Rules/RuleWith.h"
#include "../Game/Rules/RuleWithout.h"

using namespace std;

template <typename T>
class Game {
public:
	Game(int numOfOrcs, int numOfMens, int numOfElfs, int G, T rule);
	~Game() = default;
	//int scan(int& numOfOrcs, int& numOfMens, int& numOfElfs, int& G);      //считывание количества юнитов и размера поля
	void unitMove(Field& f, string character);       //двигает в поле f юнит character
	bool addUnit(Field& f);
	void delUnit(Field& f);
	void setLogger(Logger* logger_);
	void setLogFormatter(LogFormatter* formatter);
	void saveGame(string name, int turn);
	void loadGame(string name, int& G, int& turn);
	void restoreMemento(CommandMemento* memento, int &G, int& turn);
	GameMemento* readMemento(string name, int turn);

	LoggerProxy* logger;
	Field* f1;
	vector<Base*> bases;
	Base* MEb;	//Men and Elfs base
	Base* b;	//Orcs base
	StateContext states;
	T rule;
};

template class Game<RuleWith>;
template class Game<RuleWithout>;

#endif