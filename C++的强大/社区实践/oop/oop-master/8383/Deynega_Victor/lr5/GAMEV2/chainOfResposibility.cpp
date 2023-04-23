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

bool ArcherCheck::spawnSmth(int unitType, Base& attackBase, GameField& huerd, int x, int y) {
	if (type == unitType) {
		
	//	huerd.field[y * huerd.size + x].unit = new Unit;
		huerd.field[y * huerd.size + x].unit = attackBase.createArcher(x, y);
	//	std::cout << huerd.field[y * huerd.size + x].unit->type;
	//	std::cout << board.field[y * board.size + x].unit->type;
	//	board.draw();
	//	system("pause");
	//	board.putUnitOn(x, y, 1, attackBase.unitArr.size() - 1, board);
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
	//	board.putUnitOn(x, y, 3, attackBase.unitArr.size() - 1, board);
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
