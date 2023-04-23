//#pragma once
#ifndef LANDSCAPE_H
#define LANDSCAPE_H

//#include "Field.h"
#include "Warrior.h"

using namespace std;

enum Landscape_ID { Forest_ID = 0, BurningEarth_ID, UnknownLand_ID };

class Landscape {
public:
	Landscape() = default;
	virtual ~Landscape() = default;
	virtual string getLandscapeType() = 0;
	virtual string effectOfLndscp(Warrior w) = 0;
	virtual bool canWalk2timesPerTurn(Warrior w) = 0;
	Landscape* create(Landscape_ID id);     //фабричный метод
};

class Forest : public Landscape {      //в лесу можно ходить за 2х персонажей эльфов за ход
public:
	string getLandscapeType();
	string effectOfLndscp(Warrior w);
	bool canWalk2timesPerTurn(Warrior w);
};

class BurningEarth : public Landscape {  //раскаленная земля. Можно делать 2 хода за 1 раз
public:
	string getLandscapeType();
	string effectOfLndscp(Warrior w);
	bool canWalk2timesPerTurn(Warrior w);
};

class UnknownLand : public Landscape {  //неизвестные земли. Уничтожается броня юнита (становится равна 0)
public:
	string getLandscapeType();
	string effectOfLndscp(Warrior w);
	bool canWalk2timesPerTurn(Warrior w);
};

#endif