#include "Statistics.h"

Statistics::Statistics(Base* base) {
	saldo = satiety = employment = education = waterKoff = energyKoff = 0;
	auto buildings = base->getBuildings();
	for (auto& i : buildings) {
		if (dynamic_cast<Building*>(i)->classOfBuild() == APARTMENT) {
			employment -= dynamic_cast<Apartment*>(i)->getWorkmans();
			education -= dynamic_cast<Apartment*>(i)->getStudents();
		}
		else if (dynamic_cast<Building*>(i)->classOfBuild() == PRODUCTION) {
			employment += dynamic_cast<Production*>(i)->getVacancy();
		}
		else if (i->typeOfBuild() == SCHOOL) {
			education += 50;
		}
		satiety += dynamic_cast<Building*>(i)->getEat();
		saldo += dynamic_cast<Building*>(i)->getSaldo();
		waterKoff += dynamic_cast<Building*>(i)->getWater();
		energyKoff += dynamic_cast<Building*>(i)->getEnergy();
	}
}