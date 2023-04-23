#pragma once
#include "Factory.h"
#include "Base.h"
#include "GameField.h"


class TypeChecker {
public:
	int type;
	TypeChecker* next;
	virtual bool spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y);
	TypeChecker* setNext(TypeChecker* obj);
	TypeChecker();
};


class ArcherCheck : public TypeChecker {
public:
	ArcherCheck();
	bool spawnSmth(int unitType, Base& attackBase, GameField&, int x, int y);
};

class BallistaCheck : public TypeChecker {
public:
	BallistaCheck();
	bool spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y);
};

class AtFarmCheck : public TypeChecker {
public:
	AtFarmCheck();
	bool spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y);
};

class BomberCheck : public TypeChecker {
public:
	BomberCheck();
	bool spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y);
};

class BomberGeneralCheck : public TypeChecker {
public:
	BomberGeneralCheck();
	bool spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y);
};