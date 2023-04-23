#pragma once //check
#include <iostream>

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
	~GameField();
	void draw();
};

class Proxy {
public:
	GameField* gameField;
	Proxy(GameField* ptr);
	bool proxyChecker(int x, int y);
	bool proxyIsUnit(int x, int y);
	bool proxyIsLansdscape(int x, int y);
};
