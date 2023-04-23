#include "MeleeFactory.h"
#include "MeleeUnit.h"
#include "PeasantLvl1.h"
#include "KnightLvl2.h"
Unit* MeleeFactory::createLvl1Unit() {
	Unit* peasant = new PeasantLvl1();
	return peasant;
}
Unit* MeleeFactory::createLvl2Unit() {
	Unit* knight = new KnightLvl2();
	return knight;
}
