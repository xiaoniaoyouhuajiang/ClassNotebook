#include "Units.h" //check
//#include "GameField.h"
#include "FieldBlock.h"
#include <string>


Unit::Unit(){
	locateCost = 0;
	x = 0;
	y = 0;
	damage = 0;
	health = 0;
	type = 0;
}

void Unit::castFor(){}

bool Unit::relocate(int newx, int newy, GameField& board, int size) { //rewrite
	if (board.field[newy * size + newx].landType->getType() == 1 || board.field[newy * size + newx].landType->getType() == 2) {
		return false;
	}
	if ((newx >= size) || (newy >= size) || (newx == board.bx && newy == board.by)) {
		return false;
	}
	if (board.field[newy * size + newx].unit != nullptr) {
		return false;
	}
	board.field[newy * size + newx].unit = board.field[this->y * size + this->x].unit;
	board.field[this->y * size + this->x].unit = nullptr;
	board.field[newy * size + newx].unit->x = newx;
	board.field[newy * size + newx].unit->y = newy;
	return true;
}

std::string Unit::getName() {
	switch (type) {
	case 1: {
		return "Archer";
	}
	case 2: {
		return "Ballista";
	}
	case 3: {
		return "Defend farm unit";
	}
	case 4: {
		return "Attack farm unit";
	}
	case 5: {
		return "Bomber";
	}
	case 6: {
		return "Bomber-general";
	}
	}
}

std::ostream& operator<<(std::ostream& out, Unit& unit) {
	out << unit.getName() + " respowned at x = " + std::to_string(unit.x) + " y = " + std::to_string(unit.y) + "\n";
	return out;
}

Unit::~Unit() {}


LongRangeUnits::LongRangeUnits() {
	locateCost = 2;
	reLocateCost = 1;
	levelUpCost = 2;
	this->x = 0;
	this->y = 0;
	damage = 1;
	health = 1;
	targetX = 0;
	targetY = 0;
	didShoot = false;
}

LongRangeUnits::~LongRangeUnits() {}

bool LongRangeUnits::makeShot(int x, int y, GameField& board, int dmg){
	if (board.field[y * board.size + x].unit == NULL) {
		return false;
	}
	else {
		board.field[y * board.size + x].unit->health -= dmg;
		return true;
	}
}



Archer::Archer(int x, int y) {
	//add economic action
	type = 1;
	this->x = x;
	this->y = y;
}

Archer::Archer() {
	type = 1;
	x = 0;
	y = 0;

}

Archer::~Archer() {}


Ballista::Ballista(int x, int y) {
	//add economic action
	this->x = x;
	this->y = y;
	damage = 3;
	locateCost = 4;
	reLocateCost = 1;
	levelUpCost = 10;
	health = 2;
	targetX = 0;
	targetY = 0;
	didShoot = false;
	type = 2;
}

Ballista::Ballista() {
	//add economic action
	this->x = 0;
	this->y = 0;
	damage = 3;
	locateCost = 4;
	reLocateCost = 1;
	levelUpCost = 10;
	health = 2;
	targetX = 0;
	targetY = 0;
	didShoot = false;
	type = 2;
}

Ballista::~Ballista() {}


FarmUnits::FarmUnits() {
	this->x = 0;
	this->y = 0;
	locateCost = 5;
	reLocateCost = 1;
	levelUpCost = 4;
	moneyPerTurn = 2;
	health = 1;
}

FarmUnits::~FarmUnits() {}


DefendFarmUnit::DefendFarmUnit(int x, int y) {
	this->x = x;
	this->y = y;
	type = 3;
}

DefendFarmUnit::DefendFarmUnit() {
	this->x = 0;
	this->y = 0;
	type = 3;
}

DefendFarmUnit::~DefendFarmUnit() {}


AttackFarmUnit::AttackFarmUnit(int x, int y) {
	this->x = x;
	this->y = y;
	type = 4;
}

AttackFarmUnit::AttackFarmUnit() {
	this->x = x;
	this->y = y;
	type = 4;
}

AttackFarmUnit::~AttackFarmUnit() {}


MeleeUnits::~MeleeUnits(){}

MeleeUnits::MeleeUnits() {
	this->x = 0;
	this->y = 0;
	damage = 5;
	health = 2;
	locateCost = 2;
}


SuicideBomber::SuicideBomber(int x, int y) {
	this->x = x;
	this->y = y;
	type = 5;
}

SuicideBomber::SuicideBomber() {
	this->x = x;
	this->y = y;
	type = 5;
}

SuicideBomber::~SuicideBomber() {}


SuicideBomberGeneral::SuicideBomberGeneral(int x, int y) {
	this->x = x;
	this->y = y;
	damage = 8;
	health = 2;
	locateCost = 3;
	type = 6;
}

SuicideBomberGeneral::SuicideBomberGeneral() {
	this->x = x;
	this->y = y;
	damage = 8;
	health = 2;
	locateCost = 3;
	type = 6;
}

SuicideBomberGeneral::~SuicideBomberGeneral() {}

Objector::Objector(NeutralObject* ptr) {
	this->p = ptr;
}

Objector::~Objector() {
	delete p;
}

Objector::Objector() {
	this->p = NULL;
}

void operator+(Objector obj, Unit& someUnit) {
	switch (obj.p->effect()) {
	case 1: {
		someUnit.health--;
		break;
	}
	case 2: {
		if (someUnit.type == 5 || someUnit.type == 6) { //melee units
			someUnit.damage += 2;
		}
		break;
	}
	case 3: {
		if (someUnit.type == 1 || someUnit.type == 2) { //longrange units
			someUnit.damage += 2;
		}
		break;
	}
	case 4: {
		if (someUnit.type != 3) { //not farm units
			someUnit.damage *= 2;
			break;
		}
	}
	}
}
