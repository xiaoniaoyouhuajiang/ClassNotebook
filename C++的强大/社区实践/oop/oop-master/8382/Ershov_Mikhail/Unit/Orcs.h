#pragma once
#include "Warrior.h"

class Orcs : public Warrior {

public:
	Orcs();
	~Orcs();
	void SetBoost(int boost);

private:
	int boost;            //умножает здоровье и атаку на значение boost, а броню делит на (boost + 1)

};

//------------------------------------------------------

class Devourers : public Orcs {        //пожиратели
public:
	Devourers();
	~Devourers();
	int GetCounter();
	void SetCounter(int counter);

private:
	double percent;         //с вероятностью x при атаке урон умножается на 2 (т.е. атакует в того же юнита еще раз)
	int counter;
};

//------------------------------------------------------

class Robbers : public Orcs {         //разбойники
public:
	Robbers();
	~Robbers();
	int GetCounter();
	void SetCounter(int counter);

private:
	int around;            //если разбойник окружен (в упор к нему стоят минимум 2 врага), то он наносит урон всем
	int counter;
};
