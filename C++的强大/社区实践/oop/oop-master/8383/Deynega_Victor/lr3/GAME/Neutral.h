#pragma once

//#include "Units.h"

class NeutralObject {
public:
	int x;
	int y;
	virtual int effect() = 0;
};

class DeadlyPosion : public NeutralObject { //no
public:
	DeadlyPosion();
	int effect();
};

class KnivesOut : public NeutralObject { //attack melee +2
public:
	KnivesOut();
	int effect();
};

class ArrowsOut : public NeutralObject { //long range +2
public:
	ArrowsOut();
	int effect();
};

class DoubleAttack : public NeutralObject { //double anything
public:
	DoubleAttack();
	int effect();
};

class PlusDamage : public NeutralObject {
public:
	PlusDamage();
	int effect();
};