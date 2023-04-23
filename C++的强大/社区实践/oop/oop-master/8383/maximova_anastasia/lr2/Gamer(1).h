#pragma once
#include <iostream>
#include <string>
#include "GameField.h"
#include <ctime>

using namespace std;

class Gamer {
protected:
	string name;
	char team1, team2;
	char answer;

	int width;
	int height;
	int exit;
	int x, y, x2, y2;
	GameField* field;

public:
	Gamer();	
	int dataCorrect();
	void caseField();

	void caseName(int numberGamer);
	bool choice2();

	void caseAddCommand(int numberGamer);
	void addUnitRandom(char type);
	bool caseError(int command, int numberGamer);

	void caseDeleteUnit(int numberGamer);
	bool caseError(int numberGamer);

	void destination(char a, int steps);
	int checkUnit(int numberGamer);
	void caseMovUnit(int numberGamer);
	bool caseError(char a, int steps);
	void casePrintField();

	void infoUnit(int x, int y);
	void infoBase();
	void saveField();

	string getName();

	int theEnd();
};
