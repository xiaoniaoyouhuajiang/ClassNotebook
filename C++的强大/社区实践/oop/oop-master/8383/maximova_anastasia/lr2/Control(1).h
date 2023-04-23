#pragma once
#include "Gamer.h"
#include <Windows.h>

class Control {

private:
	Gamer *gamer;
	int counter;

public:
	Control();
	void BeginGame();
	void GameStart();
	void info();
};