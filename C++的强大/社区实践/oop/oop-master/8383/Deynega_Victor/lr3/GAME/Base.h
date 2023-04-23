#pragma once
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
	std::vector<Unit*> unitArr;
	Base(int size, GameField& board);
	Base(int size, GameField& board, int x, int y);
	~Base();
	
	void deleteUnit(int x, int y, GameField& board);
	Unit* createArcher(int x, int y);
	Unit* createBallista(int x, int y);
	Unit* createAtFarm(int x, int y);
	Unit* createBomber(int x, int y);
	Unit* createGeneral(int x, int y);
	void enableSpots();
	void baseHealth();
};

