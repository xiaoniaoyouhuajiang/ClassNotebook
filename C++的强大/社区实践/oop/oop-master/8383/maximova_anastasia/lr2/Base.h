#pragma once
#include "Object.h"
#include "Unit.h"
#include "AbstractFactory.h"

class Base : public Object {
protected:
	int healthBase;
	int counterUnits;
	int maxUnitsSt;
	int maxUnits;

public:
	Base(int healthBase, int maxUnits, int maxUnitsSt, int view, char name);
	void setCounterUnits(int counterUnits);

	void setName(char symbol) override {
		name[0] = symbol;
		name[1] = '\0';
	}

	void setView(int view) override {
		this->view = view;
	}

	void setXY(int x, int y) override {
		this->x = x;
		this->y = y;
	}

	void setHealthBase(int healthBase);

	int getCounterUnits();

	char* getName() override {
		return name;
	}

	int getView() override {
		return view;
	}

	int getX() override {
		return x;
	}
	int getY() override {
		return y;
	}

	int getmaxUnitsSt();
	int getMaxUnits();
	int getHealthBase();

	Base& operator -=(Unit& unit);

	virtual Unit* createUnit(int view) = 0;
};

class BasePeople : public Base {
public:
	BasePeople(int coef);

	Unit* createUnit(int view) override {
		ConcreteFactoryPeople people;
		return people.createUnit(view);
	}
};

class BaseMonster : public Base {
public:
	BaseMonster(int coef);

	Unit* createUnit(int view) override {
		ConcreteFactoryMonster monster;
		return monster.createUnit(view);
	}
};

class BaseHero : public Base {
public:
	BaseHero(int coef);

	Unit* createUnit(int view) override {
		ConcreteFactoryHero hero;
		return hero.createUnit(view);
	}
};