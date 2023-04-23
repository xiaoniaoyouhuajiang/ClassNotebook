#pragma once
#include "Unit.h"

class AbstractFactory {
public:
	virtual Unit* createUnit(int type) = 0;
};

class ConcreteFactoryMonster :public  AbstractFactory {
public:
	Unit* createUnit(int type) override {
		if (type == 1) {
			return new Vampire();
		}
		else if (type == 2) {
			return new Werewolf();
		}
	}
};

class ConcreteFactoryHero :public  AbstractFactory {
public:
	Unit* createUnit(int type) override {
		if (type == 3) {
			return new Healer();
		}
		else if (type == 4) {
			return new Magician();
		}
	}
};

class ConcreteFactoryPeople :public  AbstractFactory {
public:
	Unit* createUnit(int type) override {
		if (type == 5) {
			return new Hunter();
		}
		else if (type == 6) {
			return new Man();
		}
	}
};