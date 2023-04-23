#pragma once
#include "Base.h"

class Statistics{
private:
	int saldo;
	int employment;
	int satiety;
	int education;
	int waterKoff;
	int energyKoff;
public:
	Statistics(Base* base);
	int getSumSaldo() {
		return saldo;
	}
	int getSumEmployment() {
		return employment;
	}
	int getSumSatiety() {
		return satiety;
	}
	int getSumEducation() {
		return education;
	}
	int getSumWater() {
		return waterKoff;
	}
	int getSumEnergy() {
		return energyKoff;
	}
};

