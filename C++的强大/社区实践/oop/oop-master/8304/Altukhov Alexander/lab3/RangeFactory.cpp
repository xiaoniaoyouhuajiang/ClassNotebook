#include "RangeFactory.h"
#include "RangeUnit.h"
#include "ArcherLvl1.h"
#include "CrossbowmanLvl2.h"
Unit* RangeFactory::createLvl1Unit() {
	Unit* unit = new ArcherLvl1();
	return unit;
}
Unit* RangeFactory::createLvl2Unit() {
	Unit* unit = new CrossbowmanLvl2();
	return unit;
}