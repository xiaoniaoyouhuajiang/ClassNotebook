#include "Neutral.h"
#include <iostream>

DeadlyPosion::DeadlyPosion() {
	x = 0;
	y = 0;
}

int DeadlyPosion::effect(){
	//std::cout << "DEAD\n";
	return 1;
}


KnivesOut::KnivesOut() {
	x = 0;
	y = 0;
}

int KnivesOut::effect() { //attack melee +2
	return 2;
}

ArrowsOut::ArrowsOut() {
	x = 0;
	y = 0;
}

int ArrowsOut::effect() {
//	std::cout << "ARRRR\n";
	return 3;
}

DoubleAttack::DoubleAttack() {
	x = 0;
	y = 0;
}

int DoubleAttack::effect() {
	//std::cout << "DBL\n";
	return 4;
}

PlusDamage::PlusDamage() {
	x = 0;
	y = 0;
}

int PlusDamage::effect() {
	return 5;
}