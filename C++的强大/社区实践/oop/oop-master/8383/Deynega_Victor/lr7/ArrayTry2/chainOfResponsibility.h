#pragma once
#include "Factory.h"
#include "Base.h"
#include "GameField.h"


class TypeChecker {
public:
    bool spawnSmth(int type, GameField& board, int cell);
	TypeChecker();
    ~TypeChecker();
};
