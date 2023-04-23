#pragma once
#include "Naming.h"
#include "IUnit.h"

class INeutral{
public:
	virtual IUnit* operator += (IUnit* build) = 0;
	virtual Neutrals typeOfNeutrals() = 0;
};

class Chernozem :public INeutral {
public:
	Neutrals typeOfNeutrals() override {
		return CHERNOZEM;
	};
	IUnit* operator += (IUnit* build) override {
		if (build->typeOfBuild() == FERMA) {
			dynamic_cast<Building*>(build)->setEat(dynamic_cast<Building*>(build)->getEat() + 25);
		}
		return build;
	};
	Chernozem() = default;
};

class Relics :public INeutral {
public:
	Neutrals typeOfNeutrals() override {
		return RELICS;
	};
	IUnit* operator += (IUnit* build) override {
		if (build->typeOfBuild() == OFFICE) {
			dynamic_cast<Building*>(build)->setSaldo(dynamic_cast<Building*>(build)->getSaldo() + 80);
		}
		else if (build->typeOfBuild() == SCHOOL) {
			dynamic_cast<Building*>(build)->setSaldo(dynamic_cast<Building*>(build)->getSaldo() - 80);
		}
		return build;
	};
	Relics() = default;
};

class Radiation :public INeutral {
public:
	Neutrals typeOfNeutrals() override {
		return RADIATION;
	};
	IUnit* operator += (IUnit* build) override {
		dynamic_cast<Building*>(build)->setSaldo(-100);
		dynamic_cast<Building*>(build)->setEat(0);
		dynamic_cast<Building*>(build)->setEnergy(0);
		dynamic_cast<Building*>(build)->setWater(0);
		if (dynamic_cast<Building*>(build)->classOfBuild() == APARTMENT) {
			dynamic_cast<Apartment*>(build)->setStudents(0);
			dynamic_cast<Apartment*>(build)->setKids(0);
			dynamic_cast<Apartment*>(build)->setWorkmans(0);
		}
		else if (dynamic_cast<Building*>(build)->classOfBuild() == PRODUCTION) {
			dynamic_cast<Production*>(build)->setVacancy(0);
		}
		return build;
	};
	Radiation() = default;
};

class Gas :public INeutral {
public:
	Neutrals typeOfNeutrals() override {
		return GAS;
	};
	IUnit* operator += (IUnit* build) override {
		if (build->typeOfBuild() == POWERHOUSE) {
			dynamic_cast<Building*>(build)->setEnergy(dynamic_cast<Building*>(build)->getEnergy() + 25);
		}
		return build;
	};
	Gas() = default;
};

class FabricOfNeutral {
public:
	INeutral* creatorNeutralObject(Neutrals type) {
		switch (type){
		case CHERNOZEM:
			return new Chernozem();
		case RELICS:
			return new Relics();
		case RADIATION:
			return new Radiation();
		case GAS:
			return new Gas();
		default:
			return nullptr;
		}
	}
};