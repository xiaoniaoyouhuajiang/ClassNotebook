#pragma once //check
#include "GameField.h"
#include "Units.h"
#include <vector>


class Base {
public:
	int x;
	int y;
	int health;
	int maxUnits;
	int size;
	int numOfUnits;
    Base();
	Base(int size);
	~Base();
	
	void deleteUnit(int x, int y, GameField& board); //rework
	Unit* createArcher(int x, int y);
	Unit* createBallista(int x, int y);
	Unit* createAtFarm(int x, int y);
	Unit* createBomber(int x, int y);
	Unit* createGeneral(int x, int y);
	void enableSpots();
	void baseHealth();
	void setBase(std::vector<int> param);
	friend  std::ostream& operator<<(std::ostream& out, const Base&);
};


class DefBase : public Base{
public:
    int useless;
    DefBase(int side);
};

