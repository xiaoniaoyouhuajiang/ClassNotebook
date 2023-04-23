#include "HorsemanFactory.h"
#include "Horseman.h"
#include "LightHorsemanLvl1.h"
#include "HeavyHorsemanLvl2.h"
Unit* HorsemanFactory::createLvl1Unit() {
	Unit* unit = new LightHorsemanLvl1();
	return unit;
}
Unit* HorsemanFactory::createLvl2Unit() {
	Unit* unit = new HeavyHorsemanLvl2();
	return unit;
}