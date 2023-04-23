//#pragma once
#ifndef PROXY_H
#define PROXY_H

#include "Landscape.h"

//using namespace std;

class Proxy : public Landscape {
public:
	Proxy(Landscape* l);
	~Proxy();
	string getLandscapeType();
	string effectOfLndscp(Warrior w);
	bool canWalk2timesPerTurn(Warrior w);

private:
	Landscape* landsc;
};

#endif