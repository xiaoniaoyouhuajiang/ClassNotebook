#pragma once
#include "BoardUnit.h"
class BoardUnitFactory
{
public:
	BoardUnitFactory() {};
	virtual BoardUnit* getType(int type = 0) = 0; //возвращает виды типов
};

