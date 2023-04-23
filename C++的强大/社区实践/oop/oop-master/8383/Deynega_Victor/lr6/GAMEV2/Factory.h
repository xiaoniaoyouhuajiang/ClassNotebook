#pragma once //check
#include "Units.h"

class Factory {
public:
	virtual Unit* createUnit(int x, int y) = 0;
	virtual ~Factory();
};

class ArcherFactory : public Factory {
public:
	Unit* createUnit(int x, int y);
};

class BallistaFactory : public Factory {
public:
	Unit* createUnit(int x, int y);
};

class DefFarmFactory : public Factory {
public:
	Unit* createUnit(int x, int y);
};

class AtFarmFactory : public Factory {
public:
	Unit* createUnit(int x, int y);
};


class BomberFactory : public Factory {
public:
	Unit* createUnit(int x, int y);
};

class GeneralBombFactory : public Factory {
public:
	Unit* createUnit(int x, int y);
};

class AssasinFactory : public Factory {
public:
	Unit* createUnit(int x, int y);
};

class BufferFactory : public Factory {
public:
	Unit* createUnit(int x, int y);
};

class WallFactory : public Factory {
public:
	Unit* createUnit(int x, int y);
};

class ImmWallFactory : public Factory {
public:
	Unit* createUnit(int x, int y);
};

class HealTowFactory : public Factory {
public:
	Unit* createUnit(int x, int y);
};

class HealUnFactory : public Factory {
public:
	Unit* createUnit(int x, int y);
};

class PudgeFactory : public Factory {
public:
	Unit* createUnit(int x, int y);
};

class ComanderFactory : public Factory {
public:
	Unit* createUnit(int x, int y);
};