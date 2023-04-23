#pragma once
#include "PongoBoardUnit.h"
class PongoBaseBoardUnit;
class BoardUnitFactory
{
public:
	BoardUnitFactory(PongoBaseBoardUnit* base) : _base(base) {};
	virtual PlayableBoardUnit* createUnit(int type = 0) = 0;
	virtual PlayableBoardUnit* createUnit(QJsonObject snapshot) = 0;
protected:
	PongoBaseBoardUnit* _base;
};

