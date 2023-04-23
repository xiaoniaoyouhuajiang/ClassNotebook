#pragma once
#include "Warrior.h"

class Elfs : public Warrior {

public:
	Elfs();
	~Elfs();
	void SetBoost(int boost);

private:
	int boost;                   //умножает урон на boost + 1, броню делит на boost, здоровье оставляет неизменным

};

//------------------------------------------------------

class Archer : public Elfs {        //лучник
public:
	Archer();
	~Archer();
	int GetCounter();
	void SetCounter(int counter);

private:
	int arr;                 //наносит урон врагу, находящегося максимум через 2 клетки от лучника
	int counter;
};

//------------------------------------------------------

class Invisible : public Elfs {        //невидимка
public:
	Invisible();
	~Invisible();
	int GetCounter();
	void SetCounter(int counter);

private:
	int invis;             //становится невидимым на 3 хода (через него нельзя шагать и на него нельзя нападать)
	int counter;
};