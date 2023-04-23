#include "Units.h"
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