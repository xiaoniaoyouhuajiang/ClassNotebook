#pragma once

#include "Adapter.h"
#include "chainOfResponsibility.h"
#include "GameField.h"
#include "Base.h"

class Rules {
public:
	int key;
	Proxy* proxyField;
	Adapter logger; //add setUp loggs func
	TypeChecker* checker;// = new ArcherCheck; add setUp spawn units
	GameField* board;
	Base* attackBase;
	Rules();
	void menu();
	void unitAttackInfo();
	virtual int action(int turnCounter) = 0;
};


class Rule1 :public Rules { //destroy tower and units mode
public:
	bool menuFlag;
	Rule1();
	int whoLose();
	int action(int turnCounter);
};

class Rule2 : public Rules { //spawn max units mode
public:
	bool menuFlag;
	Rule2();
	int whoLose();
	int action(int turnCounter);
};
