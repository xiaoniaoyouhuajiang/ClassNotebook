#include "chainOfResponsibility.h"
#include "FieldBlock.h"


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

bool ArcherCheck::spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y) {
	if (type == unitType) {
		attackBase.unitArr.push_back(attackBase.createArcher(x, y));
		board.field[y * board.size + x].unit = attackBase.unitArr[attackBase.unitArr.size() - 1];
		board.putUnitOn(x, y, 1, attackBase.unitArr.size() - 1, board);
		attackBase.unitArr[attackBase.unitArr.size() - 1]->index = attackBase.unitArr.size() - 1;
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

BallistaCheck::BallistaCheck() {
	type = 2;
	next = nullptr;
}

bool BallistaCheck::spawnSmth(int unitType, Base& attackBase, GameField& board, int x, int y) {
	if (type == unitType) {
		attackBase.unitArr.push_back(attackBase.createBallista(x, y));
		board.field[y * board.size + x].unit = attackBase.unitArr[attackBase.unitArr.size() - 1];
		board.putUnitOn(x, y, 2, attackBase.unitArr.size() - 1, board); \
		attackBase.unitArr[attackBase.unitArr.size() - 1]->index = attackBase.unitArr.size() - 1;
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
		attackBase.unitArr.push_back(attackBase.createAtFarm(x, y));
		board.field[y * board.size + x].unit = attackBase.unitArr[attackBase.unitArr.size() - 1];
		board.putUnitOn(x, y, 3, attackBase.unitArr.size() - 1, board); \
		attackBase.unitArr[attackBase.unitArr.size() - 1]->index = attackBase.unitArr.size() - 1;
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
		attackBase.unitArr.push_back(attackBase.createBomber(x, y));
		board.field[y * board.size + x].unit = attackBase.unitArr[attackBase.unitArr.size() - 1];
		board.putUnitOn(x, y, 5, attackBase.unitArr.size() - 1, board); \
		attackBase.unitArr[attackBase.unitArr.size() - 1]->index = attackBase.unitArr.size() - 1;
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
		attackBase.unitArr.push_back(attackBase.createGeneral(x, y));
		board.field[y * board.size + x].unit = attackBase.unitArr[attackBase.unitArr.size() - 1];
		board.putUnitOn(x, y, 6, attackBase.unitArr.size() - 1, board); \
		attackBase.unitArr[attackBase.unitArr.size() - 1]->index = attackBase.unitArr.size() - 1;
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
