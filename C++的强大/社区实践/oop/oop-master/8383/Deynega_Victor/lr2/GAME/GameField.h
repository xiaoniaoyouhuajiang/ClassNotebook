#pragma once
#include <iostream>

class FieldBlock;

class GameField {
public:
	int size;
	int numOfEmptyBlocks;
	FieldBlock* field;
	GameField(const GameField& board);
	GameField(int side);
	GameField();
	~GameField();
	void draw();
	void putUnitOn(int x, int y, int type, int index, GameField& board);
};

class Proxy {
public:
	GameField* gameField;
	Proxy(GameField* ptr);
	bool proxyChecker(int x, int y);
	bool proxyIsUnit(int x, int y);
};