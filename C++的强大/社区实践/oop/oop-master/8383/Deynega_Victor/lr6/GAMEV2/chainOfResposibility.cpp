#include "chainOfResponsibility.h"
#include "FieldBlock.h"
#include "Factory.h"


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

bool ArcherCheck::spawnSmth(int unitType, Base& attackBase, GameField& huerd, int x, int y) {
	if (type == unitType) {
		huerd.field[y * huerd.size + x].unit = attackBase.createArcher(x, y);
		return true;
	}
	else {
		if (next) {
			if (next->spawnSmth(unitType, attackBase, huerd, x, y)) {
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

bool BallistaCheck::spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y) {
	if (type == unitType) {
		board.field[y * board.size + x].unit = attackBase.createBallista(x, y);
//		board.putUnitOn(x, y, 2, attackBase.unitArr.size() - 1, board); //
		return true;
	}
	else {
		if (next) {
			if (next->spawnSmth(unitType, attackBase, board, x, y)) {
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

bool AtFarmCheck::spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y) {
	if (type == unitType) {
		board.field[y * board.size + x].unit = attackBase.createAtFarm(x, y);
		return true;
	}
	else {
		if (next) {
			if (next->spawnSmth(unitType, attackBase, board, x, y)) {
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

bool BomberCheck::spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y) {
	if (type == unitType) {
		board.field[y * board.size + x].unit = attackBase.createBomber(x, y);
	//	board.putUnitOn(x, y, 5, attackBase.unitArr.size() - 1, board); 
		return true;
	}
	else {
		if (next) {
			if (next->spawnSmth(unitType, attackBase, board, x, y)) {
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

bool BomberGeneralCheck::spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y) {
	if (type == unitType) {
		board.field[y * board.size + x].unit = attackBase.createGeneral(x, y);
	//	board.putUnitOn(x, y, 6, attackBase.unitArr.size() - 1, board); 
		return true;
	}
	else {
		if (next) {
			if (next->spawnSmth(unitType, attackBase, board, x, y)) {
				return true;
			}
		}
	}
	return false;
}

bool TypeChecker::spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y) {
	return false;
}


AssasinCheck::AssasinCheck() {
	type = 7;
	next = nullptr;
}

bool AssasinCheck::spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y) {
	if (type == unitType) {
		AssasinFactory fac;
		board.field[y * board.size + x].unit = fac.createUnit(x, y);
		return true;
	}
	else {
		if (next) {
			if (next->spawnSmth(unitType, attackBase, board, x, y)) {
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

bool BufferCheck::spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y) {
	if (type == unitType) {
		BufferFactory fac;
		board.field[y * board.size + x].unit = fac.createUnit(x, y);
		return true;
	}
	else {
		if (next) {
			if (next->spawnSmth(unitType, attackBase, board, x, y)) {
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

bool WallCheck::spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y) {
	if (type == unitType) {
		WallFactory fac;
		board.field[y * board.size + x].unit = fac.createUnit(x, y);
		return true;
	}
	else {
		if (next) {
			if (next->spawnSmth(unitType, attackBase, board, x, y)) {
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

bool ImmWallCheck::spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y) {
	if (type == unitType) {
		ImmWallFactory fac;
		board.field[y * board.size + x].unit = fac.createUnit(x, y);
		return true;
	}
	else {
		if (next) {
			if (next->spawnSmth(unitType, attackBase, board, x, y)) {
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

bool HealTowCheck::spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y) {
	if (type == unitType) {
		HealTowFactory fac;
		board.field[y * board.size + x].unit = fac.createUnit(x, y);
		return true;
	}
	else {
		if (next) {
			if (next->spawnSmth(unitType, attackBase, board, x, y)) {
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

bool HealUnCheck::spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y) {
	if (type == unitType) {
		HealUnFactory fac;
		board.field[y * board.size + x].unit = fac.createUnit(x, y);
		return true;
	}
	else {
		if (next) {
			if (next->spawnSmth(unitType, attackBase, board, x, y)) {
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

bool PudgeCheck::spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y) {
	if (type == unitType) {
		PudgeFactory fac;
		board.field[y * board.size + x].unit = fac.createUnit(x, y);
		return true;
	}
	else {
		if (next) {
			if (next->spawnSmth(unitType, attackBase, board, x, y)) {
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

bool ComanderCheck::spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y) {
	if (type == unitType) {
		ComanderFactory fac;
		board.field[y * board.size + x].unit = fac.createUnit(x, y);
		return true;
	}
	else {
		if (next) {
			if (next->spawnSmth(unitType, attackBase, board, x, y)) {
				return true;
			}
		}
	}
	return false;
}