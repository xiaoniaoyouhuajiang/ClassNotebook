#pragma once
#include "GameField.h"
#include "Gamer.h"

class Dialog {		//для взаимодействия с игроками и вызова методов
private:
	char answer;
	int exit;

public:

	Dialog();
	void caseStart();
	bool choice();
	void rules();
	void infoUnit();
};

