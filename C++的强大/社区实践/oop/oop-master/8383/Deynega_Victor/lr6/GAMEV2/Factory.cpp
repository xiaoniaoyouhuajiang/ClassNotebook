#include "Units.h" //check
#include "Factory.h"

Factory::~Factory() {}

Unit* ArcherFactory::createUnit(int x, int y) {
	Archer* bowman = new Archer;
	bowman->x = x;
	bowman->y = y;
	return bowman;
}

Unit* BallistaFactory::createUnit(int x, int y) {
	Ballista* bigBow = new Ballista;
	bigBow->x = x;
	bigBow->y = y;
	return bigBow;
}

Unit* DefFarmFactory::createUnit(int x, int y) {
	DefendFarmUnit* defFarm = new DefendFarmUnit;
	defFarm->x = x;
	defFarm->y = y;
	return defFarm;
}

Unit* AtFarmFactory::createUnit(int x, int y) {
	AttackFarmUnit* atFarm = new AttackFarmUnit;
	atFarm->x = x;
	atFarm->y = y;
	return atFarm;
}

Unit* BomberFactory::createUnit(int x, int y) {
	SuicideBomber* bomber = new SuicideBomber;
	bomber->x = x;
	bomber->y = y;
	return bomber;
}

Unit* GeneralBombFactory::createUnit(int x, int y) {
	SuicideBomberGeneral* general = new SuicideBomberGeneral;
	general->x = x;
	general->y = y;
	return general;
}

Unit* AssasinFactory::createUnit(int x, int y) {
	Assasin* unit = new Assasin;
	unit->x = x;
	unit->y = y;
	return unit;
}

Unit* BufferFactory::createUnit(int x, int y) {
	Buffer* unit = new Buffer;
	unit->x = x;
	unit->y = y;
	return unit;
}

Unit* WallFactory::createUnit(int x, int y) {
	Wall* unit = new Wall;
	unit->x = x;
	unit->y = y;
	return unit;
}

Unit* ImmWallFactory::createUnit(int x, int y) {
	ImmortalWall* unit = new ImmortalWall;
	unit->x = x;
	unit->y = y;
	return unit;
}

Unit* HealTowFactory::createUnit(int x, int y) {
	HealTower* unit = new HealTower;
	unit->x = x;
	unit->y = y;
	return unit;
}

Unit* HealUnFactory::createUnit(int x, int y) {
	HealUnit* unit = new HealUnit;
	unit->x = x;
	unit->y = y;
	return unit;
}

Unit* PudgeFactory::createUnit(int x, int y) {
	Pudge* unit = new Pudge;
	unit->x = x;
	unit->y = y;
	return unit;
}

Unit* ComanderFactory::createUnit(int x, int y) {
	Comander* unit = new Comander;
	unit->x = x;
	unit->y = y;
	return unit;
}