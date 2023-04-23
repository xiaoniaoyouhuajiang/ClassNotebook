#pragma once
#include "Gamer.h"

class Funct { //абстрактный класс
protected:
	string command;	//действие
	char act;
	int x, y;		//местоположение юнита
	int idGamer;
	Gamer* pointer;
public:
	virtual void setPointer(Gamer* gamer) = 0;
	virtual void setParam(string cmmnd) = 0;
	virtual void recognizer() = 0;
	//virtual void help() = 0;
};

