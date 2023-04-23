#include "chainOfResponsibility.h"
#include "FieldBlock.h"
#include "Factory.h"

TypeChecker::TypeChecker(){}
TypeChecker::~TypeChecker(){}

bool TypeChecker::spawnSmth(int type, GameField &board, int cell){

    if(type == 1){
        ArcherFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
        return true;
    }
    if(type == 2){
        BallistaFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
        return true;
    }
    if(type == 5){
        BomberFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
        return true;
    }
    if(type == 6){
        GeneralBombFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
        return true;
    }
    if(type == 7){
        AssasinFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
        return true;
    }
    if(type == 8){
        BufferFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
        return true;
    }
    if(type == 9){
        WallFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
        return true;
    }
    if(type == 10){
        ImmWallFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
        return true;
    }
    if(type == 11){
        HealTowFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
        return true;
    }
    if(type == 12){
        HealUnFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
        return true;
    }
    if(type == 13){
        PudgeFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
        return true;
    }
    if(type == 14){
        ComanderFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
        return true;
    }
    return false;
}

/*
TypeChecker::TypeChecker() {
	type = 0;
	next = nullptr;
}

TypeChecker* TypeChecker::setNext(TypeChecker* obj) {
	next = obj;
	return next;
}

ArcherCheck::ArcherCheck() {
	type = 1;
	next = nullptr;
}

bool ArcherCheck::spawnSmth(int unitType, GameField& board, int cell) {
    ArcherFactory fac;
	if (type == unitType) {
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
		return true;
	}
	else {
		if (next) {
            if (next->spawnSmth(unitType, board, cell)) {
				return true;
			}
		}
	}
	return false;
}

BallistaCheck::BallistaCheck() {
	type = 2;
	next = nullptr;
}

bool BallistaCheck::spawnSmth(int unitType, GameField& board, int cell) {
	if (type == unitType) {
        BallistaFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
		return true;
	}
	else {
		if (next) {
            if (next->spawnSmth(unitType, board, cell)) {
				return true;
			}
		}
	}
	return false;
}

AtFarmCheck::AtFarmCheck() {
	type = 3;
	next = nullptr;
}

bool AtFarmCheck::spawnSmth(int unitType, GameField& board, int cell) {
	if (type == unitType) {
        AtFarmFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
		return true;
	}
	else {
		if (next) {
            if (next->spawnSmth(unitType, board, cell)) {
				return true;
			}
		}
	}
	return false;
}

BomberCheck::BomberCheck() {
	type = 5;
	next = nullptr;
}

bool BomberCheck::spawnSmth(int unitType, GameField& board, int cell) {
	if (type == unitType) {
        BomberFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
		return true;
	}
	else {
		if (next) {
            if (next->spawnSmth(unitType, board, cell)) {
				return true;
			}
		}
	}
	return false;
}

BomberGeneralCheck::BomberGeneralCheck() {
	type = 6;
	next = nullptr;
}

bool BomberGeneralCheck::spawnSmth(int unitType, GameField& board, int cell) {
	if (type == unitType) {
        GeneralBombFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
		return true;
	}
	else {
		if (next) {
            if (next->spawnSmth(unitType, board, cell)) {
				return true;
			}
		}
	}
	return false;
}

bool TypeChecker::spawnSmth(int unitType, GameField& board, int cell) {
	return false;
}


AssasinCheck::AssasinCheck() {
	type = 7;
	next = nullptr;
}

bool AssasinCheck::spawnSmth(int unitType, GameField& board, int cell) {
	if (type == unitType) {
		AssasinFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
		return true;
	}
	else {
		if (next) {
            if (next->spawnSmth(unitType, board, cell)) {
				return true;
			}
		}
	}
	return false;
}


BufferCheck::BufferCheck() {
	type = 8;
	next = nullptr;
}

bool BufferCheck::spawnSmth(int unitType, GameField& board, int cell) {
	if (type == unitType) {
		BufferFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
		return true;
	}
	else {
		if (next) {
            if (next->spawnSmth(unitType, board, cell)) {
				return true;
			}
		}
	}
	return false;
}


WallCheck::WallCheck() {
	type = 9;
	next = nullptr;
}

bool WallCheck::spawnSmth(int unitType, GameField& board, int cell) {
	if (type == unitType) {
		WallFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
		return true;
	}
	else {
		if (next) {
            if (next->spawnSmth(unitType, board, cell)) {
				return true;
			}
		}
	}
	return false;
}

ImmWallCheck::ImmWallCheck() {
	type = 10;
	next = nullptr;
}

bool ImmWallCheck::spawnSmth(int unitType, GameField& board, int cell) {
	if (type == unitType) {
		ImmWallFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
		return true;
	}
	else {
		if (next) {
            if (next->spawnSmth(unitType, board, cell)) {
				return true;
			}
		}
	}
	return false;
}

HealTowCheck::HealTowCheck() {
	type = 11;
	next = nullptr;
}

bool HealTowCheck::spawnSmth(int unitType, GameField& board, int cell) {
	if (type == unitType) {
		HealTowFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
		return true;
	}
	else {
		if (next) {
            if (next->spawnSmth(unitType, board, cell)) {
				return true;
			}
		}
	}
	return false;
}

HealUnCheck::HealUnCheck() {
	type = 12;
	next = nullptr;
}

bool HealUnCheck::spawnSmth(int unitType, GameField& board, int cell) {
	if (type == unitType) {
		HealUnFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
		return true;
	}
	else {
		if (next) {
            if (next->spawnSmth(unitType, board, cell)) {
				return true;
			}
		}
	}
	return false;
}

PudgeCheck::PudgeCheck() {
	type = 13;
	next = nullptr;
}

bool PudgeCheck::spawnSmth(int unitType, GameField& board, int cell) {
	if (type == unitType) {
		PudgeFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
		return true;
	}
	else {
		if (next) {
            if (next->spawnSmth(unitType, board, cell)) {
				return true;
			}
		}
	}
	return false;
}


ComanderCheck::ComanderCheck() {
	type = 14;
	next = nullptr;
}

bool ComanderCheck::spawnSmth(int unitType, GameField& board, int cell) {
	if (type == unitType) {
		ComanderFactory fac;
        board.field[cell].unit = fac.createUnit(cell%15, cell/15);
		return true;
	}
	else {
		if (next) {
            if (next->spawnSmth(unitType, board, cell)) {
				return true;
			}
		}
	}
	return false;
}
*/
