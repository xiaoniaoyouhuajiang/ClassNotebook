#pragma once
#include "Gamer.h"
#include <string>
#include <vector>
#include "Funct.h"
#include "BaseFunct.h"

void BaseFunct::recoveryBase() {
	x = command[2] - '0';
	y = command[3] - '0';
	int x2 = command[4] - '0';
	int y2 = command[5] - '0';
	pointer->recoveryBases(x, y, x2, y2);
}

void BaseFunct::attackBase() {
	x = command[2] - '0';
	y = command[3] - '0';
	char direct = command[4];	  // направление движения
	int steps = command[5] - '0'; // кол-во шагов
	int flagAttack = command[6] - '0';

	pointer->caseMovUnit(idGamer, x, y, direct, steps, flagAttack);
}

void BaseFunct::infoBase() {
	pointer->infoBase(act);
}
