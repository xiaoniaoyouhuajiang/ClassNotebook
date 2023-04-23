#include "Units.h" //check
//#include "GameField.h"
#include "NeutralFactory.h"
#include "FieldBlock.h"
#include <string>
#include <cmath>


Unit::Unit(){
	locateCost = 0;
	x = 0;
	y = 0;
	damage = 0;
	health = 0;
	type = 0;
}

void Unit::castFor(){}


int Unit::atack(int cell1, int cell2, GameField &board){ //buffer, comander, heal, pudge
    if(cell1 == cell2) return 0;
    double distant = sqrt((((cell1%15)-(cell2%15))*((cell1%15)-(cell2%15))) + (((cell1/15)-(cell2/15))*((cell1/15)-(cell2/15))));
    if(distant > 1.5){
        return 0;
    }
    if(cell2 == 5 ) return 0;
    if(cell2 == (14*15+9)){
        return 9;
    }
    if(board.field[cell2].landType->getType() != 0) return 0;
    if(board.field[cell2].getUnitType() == 0) return 0;
    board.field[cell2].unit->health-=board.field[cell1].unit->damage;
    if(board.field[cell2].unit->health <= 0){
        board.field[cell2].unit = nullptr;
        return 4;
    }
    return 0;
}


int Unit::relocate(int newx, int newy, GameField& board, int size) {
    if(newx == x && newy == y) return 0;
    int newCell = newy * size + newx;
    if (board.field[newCell].landType->getType() == 1 || board.field[newCell].landType->getType() == 2) {
        return 2;
	}
    if (board.field[newCell].unit != nullptr) {
        return 2;
	}
    if((newx == 5 && newy == 0) || (newx == 9 && newy == 14)){
        return 2;
    }
    int tmp = this->y * size + this->x;
    board.field[tmp].unit->x = newx;
    board.field[tmp].unit->y = newy;
    int tmp2 = newy * size + newx;
    board.field[tmp2].unit = board.field[tmp].unit;
    board.field[tmp].unit = nullptr;
    return 1;
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
	case 7: {
		return "Assasin";
	}
	case 8: {
		return "Buffer";
	}
	case 9: {
		return "Regular wall";
	}
	case 10: {
		return "Immortal wall";
	}
	case 11: {
		return "Tower heal";
	}
	case 12: {
		return "Unit heal";
	}
	case 13: {
		return "Pudge";
	}
	case 14: {
		return "Comander";
	}
	}
	return "NOTHING";
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

int MeleeUnits::relocate(int x, int y, GameField &board, int size){
    if(this->x == x && this->y == y) return 0;
    int targetCell = y * size + x;
    int unitCell = this->y * size + this->x;
    double distant = sqrt(((x-(this->x))*(x-(this->x))) + ((y-(this->y))*(y-(this->y))));
    if(distant > 1.0){
        return 0;
    }
    if(x == 5 && y == 0){
        return 2;
    }
    if(x == 9 && y == 14){
        return 10;
    }
    if (board.field[targetCell].landType->getType() == 1 || board.field[targetCell].landType->getType() == 2) {
        return 2;
    }
    if (board.field[targetCell].unit != nullptr) {
        board.field[targetCell].unit->health-=board.field[unitCell].unit->damage;
        if(board.field[targetCell].unit->health <= 0){
            board.field[targetCell].unit = nullptr;
            board.field[unitCell].unit = nullptr;
            return 3;
        }
        board.field[unitCell].unit = nullptr;
        return 2;
    }
    board.field[unitCell].unit->x = x;
    board.field[unitCell].unit->y = y;
    board.field[targetCell].unit = board.field[unitCell].unit;
    board.field[unitCell].unit = nullptr;
    return 1;
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

int SuicideBomberGeneral::relocate(int x, int y, GameField &board, int size){
    if(this->x == x && this->y == y) return 0;
    int targetCell = y * size + x;
    int unitCell = this->y * size + this->x;
    double distant = sqrt(((x-(this->x))*(x-(this->x))) + ((y-(this->y))*(y-(this->y))));
    if(distant > 1.0){
        return 0;
    }
    if(x == 5 && y == 0){
        return 2;
    }
    if(x == 9 && y == 14){
        return 10;
    }
    if(y != this->y + 1) return 0;
    if (board.field[targetCell].landType->getType() == 1 || board.field[targetCell].landType->getType() == 2) {
        return 2;
    }
    if (board.field[targetCell].unit != nullptr) {
        board.field[targetCell].unit->health-=board.field[unitCell].unit->damage;
        if(board.field[targetCell].unit->health <= 0){
            board.field[targetCell].unit = nullptr;
            board.field[unitCell].unit = nullptr;
            return 3;
        }
        board.field[unitCell].unit = nullptr;
        return 2;
    }
    board.field[unitCell].unit->x = x;
    board.field[unitCell].unit->y = y;
    board.field[targetCell].unit = board.field[unitCell].unit;
    board.field[unitCell].unit = nullptr;
    return 1;
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
    //delete p;
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

Assasin::Assasin() {
	this->x = 0;
	this->y = 0;
	damage = 2;
	health = 1;
	type = 7;
	locateCost = 1;
}

Assasin::~Assasin() {
}


Buffer::Buffer() {
	this->x = 0;
	this->y = 0;
    damage = 1;
    health = 3;
	locateCost = 1;
	type = 8;
}


Buffer::~Buffer() {
}

void Buffer::buff(int x, int y, GameField& board) {
    if(this->x == x && this->y == y) return;
    if((x == 5 && y == 0) || (x == 9 && y == 14)) return;
    int tmp = y * board.size + x;
    if (board.field[tmp].getUnitType() == 0) return;
    board.field[tmp].unit->health++;
    board.field[tmp].unit->damage++;
}


//DEFWND UNITS------------------------------------//
Wall::Wall() {
	this->x = 0;
	this->y = 0;
	damage = 0;
    health = 1;
	locateCost = 1;
	type = 9;
}

Wall::~Wall() { }


ImmortalWall::ImmortalWall() {
	liveTime = 2;
	this->x = 0;
	this->y = 0;
	damage = 0;
	health = 100000;
	type = 10;
	locateCost = 0;
}

ImmortalWall::~ImmortalWall() { }

HealTower::HealTower() {
	heal = 1;
	this->x = 0;
	this->y = 0;
	type = 11;
	damage = 1;
	health = 2;
	locateCost = 1;
}

HealTower::~HealTower() { }


HealUnit::HealUnit() {
	heal = 1;
	this->x = 0;
	this->y = 0;
	damage = 1;
	type = 12;
	health = 2;
	locateCost = 1;
}

HealUnit::~HealUnit() { }


Pudge::Pudge() {
	this->x = 0;
	this->y = 0;
	damage = 1;
	health = 2;
	locateCost = 1;
	type = 13;
}

int Pudge::hook(int x, int y, GameField& board) {
    if((x == 5 && y == 0) || (x == 9 && y == 14)) return 0;
    if(this->x == x && this->y == y) return 0;
    if (this->x != x) return 0;
    if(this->y < y) return 0;
    int unitCell = y*15 + x;
    if(board.field[unitCell].getUnitType() == 0) return 0;
    if(board.field[unitCell].landType->getType() != 0) return 0;
    if((y+1) == this->y) return 0;

    int newCell = (this->y - 1)*15 + x;
    if(board.field[newCell].getUnitType() != 0 || board.field[newCell].landType->getType() != 0){
        board.field[unitCell].unit = nullptr;
        return 7;
    }
    board.field[unitCell].unit->y = this->y - 1;
    board.field[newCell].unit = board.field[unitCell].unit;
    board.field[unitCell].unit = nullptr;
    return 8;
}

Pudge::~Pudge() { }



Comander::Comander() {
	this->x = 0;
	this->y = 0;
	damage = 2;
	health = 2;
	locateCost = 1;
	type = 14;
}

Comander::~Comander() { }

void Comander::poising(int x, int y, GameField& board) {
    if((x == 5 && y == 0) || (x == 9 && y == 14)) return;
    if(this->x == x && this->y == y) return;
    double distant = sqrt(((x-(this->x))*(x-(this->x))) + ((y-(this->y))*(y-(this->y))));
    int areaCell = y*15 + x;
    if(distant > 1.5){
        return;
    }
    if(board.field[areaCell].landType->getType() != 0){
        return;
    }
    board.field[areaCell].landType = new Mountain; //kostyl
}


void Comander::increase(int x, int y, GameField& board) {
    if(this->x == x && this->y == y) return;
     double distant = sqrt(((x-(this->x))*(x-(this->x))) + ((y-(this->y))*(y-(this->y))));
     if(distant > 1.5){
         return;
     }
     int unitCell = y*15 + x;
     if(board.field[unitCell].getUnitType() != 0){
         board.field[unitCell].unit->damage+=2;
     }
}


int Assasin::atack(int cell1, int cell2, GameField &board){
    if(cell1 == cell2) return 0;
    if(cell2 == 5 ) return 0;
    if(cell2 == (14*15+9)){
        return 9;
    }
    if (board.field[cell2].getUnitType() == 0) {
        board.field[cell1].unit->relocate(cell2%15, cell2/15, board, board.size);
        return 5;
    }
    board.field[cell2].unit->health -= this->damage;
    if (board.field[cell2].unit->health <= 0) {
        board.field[cell2].unit = nullptr;
        this->relocate(cell2%15, cell2/15, board, board.size);
        return 6;
    }
    return 0;
}

int LongRangeUnits::atack(int cell1, int cell2, GameField &board){
    if(cell1 == cell2) return 0;
    if(cell1/15 > cell2/15) return 0;
    if(abs(cell1/15-cell2/15) == abs(cell1%15-cell2%15)){ //diag % - get x, / - get y
        if(cell2%15 < cell1%15){
            for(int i = cell1; i < cell2+1; i+=14){
                if(board.field[i].landType->getType() == 1){
                    return 0;
                }
            }
            if(cell2 == 5 ) return 0;
            if(cell2 == (14*15+9)){
                return 9;
            }
            if(board.field[cell2].getUnitType() == 0) return 0;
            board.field[cell2].unit->health-=board.field[cell1].unit->damage;
            if(board.field[cell2].unit->health <= 0){
                return 4;
            }
        }
        if(cell2%15 > cell1%15){
            for(int i = cell1; i < cell2+1; i+=16){
                if(board.field[i].landType->getType() == 1){
                    return 0;
                }
            }
            if(cell2 == 5 ) return 0;
            if(cell2 == (14*15+9)){
                return 9;
            }
            if(board.field[cell2].getUnitType() == 0) return 0;
            board.field[cell2].unit->health-=board.field[cell1].unit->damage;
            if(board.field[cell2].unit->health <= 0){
                return 4;
            }
        }
    }
    return 0;
}



int Wall::atack(int cell1, int cell2, GameField &board){
    return 0;
}


int ImmortalWall::atack(int cell1, int cell2, GameField &board){
    return 0;
}


int Comander::relocate(int x, int y, GameField &board, int size){
    if(this->x == x && this->y == y) return 0;
    int targetCell = y * size + x;
    int unitCell = this->y * size + this->x;
    double distant = sqrt(((x-(this->x))*(x-(this->x))) + ((y-(this->y))*(y-(this->y))));
    if(distant > 1.5){
        return 0;
    }
    if (board.field[targetCell].landType->getType() == 1 || board.field[targetCell].landType->getType() == 2) {
        return 2;
    }
    if((x == 5 && y == 0) || (x == 9 && y == 14)){
        return 2;
    }
    if (board.field[targetCell].unit != nullptr) {
        return 2;
    }
    board.field[unitCell].unit->x = x;
    board.field[unitCell].unit->y = y;
    board.field[targetCell].unit = board.field[unitCell].unit;
    board.field[unitCell].unit = nullptr;
    return 1;
}

int Buffer::relocate(int x, int y, GameField &board, int size){
    if(this->x == x && this->y == y) return 0;
    int targetCell = y * size + x;
    int unitCell = this->y * size + this->x;
    double distant = sqrt(((x-(this->x))*(x-(this->x))) + ((y-(this->y))*(y-(this->y))));
    if(distant > 1.5){
        return 0;
    }
    if (board.field[targetCell].landType->getType() == 1 || board.field[targetCell].landType->getType() == 2) {
        return 2;
    }
    if((x == 5 && y == 0) || (x == 9 && y == 14)){
        return 2;
    }
    if (board.field[targetCell].unit != nullptr) {
        return 2;
    }
    board.field[unitCell].unit->x = x;
    board.field[unitCell].unit->y = y;
    board.field[targetCell].unit = board.field[unitCell].unit;
    board.field[unitCell].unit = nullptr;
    return 1;
}

void HealUnit::unitHeal(int cell, GameField& board){
    if(board.field[cell].getUnitType() == 0) return;
    board.field[cell].unit->health+=this->heal;
}

void HealTower::towerHeal(int cell, GameField& board){
    return;
}

int Ballista::relocate(int x, int y, GameField &board, int size){
    if(this->x == x && this->y == y) return 0;
    int targetCell = y * size + x;
    int unitCell = this->y * size + this->x;
    double distant = sqrt(((x-(this->x))*(x-(this->x))) + ((y-(this->y))*(y-(this->y))));
    if(distant > 1.0){
        return 0;
    }
    if (board.field[targetCell].landType->getType() == 1 || board.field[targetCell].landType->getType() == 2) {
        return 2;
    }
    if((x == 5 && y == 0) || (x == 9 && y == 14)){
        return 2;
    }
    if (board.field[targetCell].unit != nullptr) {
        return 2;
    }
    board.field[unitCell].unit->x = x;
    board.field[unitCell].unit->y = y;
    board.field[targetCell].unit = board.field[unitCell].unit;
    board.field[unitCell].unit = nullptr;
    return 1;
}



