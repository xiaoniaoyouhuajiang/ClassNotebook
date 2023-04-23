#pragma once
#include "Gamer.h"
#include <string>
#include <vector>
#include "Funct.h"
class BaseFunct : public Funct {
public:
	void setPointer(Gamer* gamer) override {
		pointer = gamer;
	}

	void setParam(string cmmnd) override {
		this->command = cmmnd;
		act = command[0];
		idGamer = command[1] - '0';
		recognizer();
	}

	void recognizer() override {
		switch (act) {
		case 'm':
			infoBase();
			break;
		case 'g':
			infoBase();
			break;
		case 'p':
			infoBase();
			break;
		case 'r':
			recoveryBase();
			break;
		case 'a':
			attackBase();
			break;
		}
	}

	void recoveryBase();
	void attackBase();
	void infoBase();
	//void help() override {}
};