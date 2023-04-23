#pragma once //check
#include <iostream>
#include "Memento.h"
#include<vector>

class FieldBlock;

class GameField {
public:
	int size;
	int bx;
	int by;
	int numOfEmptyBlocks; //??
	FieldBlock* field;
	GameField(const GameField& board);
	GameField(int side);
	GameField();
	~GameField();
	void draw();
	Memento* createMemento(int health, int turn, int units);
	bool loadMemento(std::vector<int>& param);
};

class Proxy {
public:
	GameField* gameField;
	Proxy(GameField* ptr);
	bool proxyChecker(int x, int y);
	bool proxyIsUnit(int x, int y);
	bool proxyIsLansdscape(int x, int y);
};
