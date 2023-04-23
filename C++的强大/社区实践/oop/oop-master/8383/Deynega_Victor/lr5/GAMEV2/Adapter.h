#pragma once
#include <sstream>
#include "ProxyLogger.h"
#include "Units.h"
#include "Base.h"

class Adapter: public ProxyLogger {
public:
	Adapter();
	void printAttack(Unit* unit, Unit* sunit);
	void printBase(Base* base);
	void printMove(Unit* unit, int oldX, int oldY);
	void printResUnit(Unit* unit);
	void printDeathUnit(Unit* unit);
};