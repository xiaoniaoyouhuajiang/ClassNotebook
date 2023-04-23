#pragma once
#include "Gamer.h"
#include "Funct.h"

class UnitFunct : public Funct {

public:

	void setPointer(Gamer* gamer) override {
		pointer = gamer;
	}

	void setParam(string cmmnd) override {
		this->command = cmmnd;
		act = command[0];
		idGamer = command[1] - '0';
		x = command[2] - '0';
		y = command[3] - '0';
		recognizer();
	}

	void recognizer() override {
		switch (act) {
		case 'h':
			help();
			break;

		case 'm':
			movUnit();
			break;

		case 'i':
			infoUnit();
			break;

		case 'c':
			swapUnit();
			break;
		}
	}

	//перемещение своих юнитов

	void movUnit();
	void infoUnit();
	void swapUnit();
	void help();
};

