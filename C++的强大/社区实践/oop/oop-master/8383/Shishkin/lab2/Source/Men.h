#pragma once
#include "Warrior.h"

class Men : public Warrior {

public:
	Men();
	~Men();
	void SetBoost(int boost);

private:
	int boost;                   //умножает урон и броню на boost, здоровье делит на boost

};

//------------------------------------------------------

class Spearman : public Men {        //копьеносец
public:
	Spearman();
	~Spearman();
	int GetCounter();
	void SetCounter(int counter);

private:
	int barbecue;         //если за врагом сразу же стоит еще один враг, то урон наносится обоим
	int counter;
};

//------------------------------------------------------

class Wizard : public Men {        // маг
public:
	Wizard();
	~Wizard();
	int GetCounter();
	void SetCounter(int counter);

private:
	int range;         //может нанести урон, поделенный на 3, врагу на любом расстоянии
	int counter;
};
