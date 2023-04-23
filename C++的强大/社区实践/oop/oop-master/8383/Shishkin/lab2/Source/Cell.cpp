#include "Cell.h"

Cell::Cell() {
	neutObj = nullptr;
	landsc = nullptr;
}

Cell::~Cell() {
	delete neutObj;
	neutObj = nullptr;
	delete landsc;
	landsc = nullptr;
}

Cell::Cell(const Cell& cell) : neutObj(cell.neutObj), landsc(cell.landsc) {
	warrior = cell.warrior;
}

Cell::Cell(Cell&& cell) : warrior(std::move(cell.warrior)), neutObj(std::move(cell.neutObj)) {
	cell.warrior.~Warrior();
	cell.neutObj = nullptr;
}

Cell& Cell::operator= (const Cell& cell) {
	if (&cell == this)
		return *this;
	delete neutObj;
	delete landsc;
	warrior = std::move(cell.warrior);
	neutObj = std::move(cell.neutObj);
	delete cell.neutObj;
	landsc = std::move(cell.landsc);
	delete cell.landsc;
	return *this;
}

Cell& Cell::operator= (Cell&& cell) {
	if (&cell == this)
		return *this;

	warrior = std::move(cell.warrior);
	neutObj = std::move(cell.neutObj);

	return *this;
}

void Cell::delNeutral() {
	delete neutObj;
	neutObj = nullptr;
}

void Cell::addUnit(Warrior u) {
	warrior = std::move(u);
}

bool Cell::isUnitFree()  {
	return warrior.GetValue() == "---";
}

Warrior Cell::getUnit() const {
	return warrior;
}

NeutralObject* Cell::getNeutral() {
	return neutObj;
}

void Cell::setNeutral(NeutralObject* obj) {
	neutObj = obj;
}

Landscape * Cell::getLandscape() const {
	return landsc;
}

void Cell::setLandscape(Landscape* value) {
	landsc = value;
}

Warrior Cell::moveUnit(Warrior w) {
	warrior = w;

	w.SetValue("---");
	return w;
}