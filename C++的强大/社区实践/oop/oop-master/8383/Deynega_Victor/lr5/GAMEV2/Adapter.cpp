#include "Adapter.h"


Adapter::Adapter() { }

void Adapter::printAttack(Unit* unit, Unit* sunit) {
	std::string newStr;
	print(unit->getName() + " with cords " + std::to_string(unit->x) + " " + std::to_string(unit->y) + " attacking " + sunit->getName() + " with cords " + std::to_string(sunit->x) + " " + std::to_string(sunit->y) + " with damage " + std::to_string(unit->damage) + "\n");
}

void Adapter::printBase(Base* base) {
	std::ostringstream tmp;
	tmp << *base;
	print(tmp.str());
}

void Adapter::printMove(Unit* unit, int oldX, int oldY) {
	print(unit->getName() + " with cords " + std::to_string(oldX) + " " + std::to_string(oldY) + " move to cell with x = " + std::to_string(unit->x) + " y = " + std::to_string(unit->y) + "\n");
}

void Adapter::printResUnit(Unit* unit) {
	std::ostringstream tmp;
	tmp << *unit;
	print(tmp.str());
}

void Adapter::printDeathUnit(Unit* unit) {
	print(unit->getName() + " with x = " + std::to_string(unit->x) + " y = " + std::to_string(unit->y) + " is dead.\n");
}