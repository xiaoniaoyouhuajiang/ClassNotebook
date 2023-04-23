#pragma once
#include "Adapter.h"
#include "chainOfResponsibility.h"
#include "GameField.h"
#include "Base.h"

class MainWindow;

class Rules {
public:
	int key;
    int actionType;
	Proxy* proxyField;
	Adapter logger; //add setUp loggs func
	TypeChecker* checker;// = new ArcherCheck; add setUp spawn units
	GameField* board;
	Base* attackBase;
    DefBase* defBase;
    int getType(int cell);
	Rules();
    void openMenu(MainWindow* window, int& turnCounter);
    void openActionMenu(MainWindow* window, int type);
};


class Rule1 :public Rules { //destroy tower and units mode
public:
    int past;
    bool attackFlag;
    int current;
    bool exitFlag;
    int visualisingFlag;
    int typeUnit1;
    int typeUnit2;
	Rule1();
    void passiveMoves();
    int whoLose();
    int action(int& turnCounter, int cell, MainWindow* window);
    void unitAction(int cell,  MainWindow* window, int& turnCounter);
    void relocateAttack(MainWindow* window);
    void setNumOfUnits(int turnCounter, bool flag);
    void exitGame();
    void showEndGameMenu(MainWindow* window);
    //int spawnUnit
   // void landCellAction(int cell, MainWindow* window);

};
