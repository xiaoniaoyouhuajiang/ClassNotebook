#pragma once
#include "UnitsFunct.h"
#include "BaseFunct.h"

#include "Gamer.h"
#include <vector>

class Facade{
private:
	UnitFunct* UF;
	BaseFunct* BF;
	Gamer* pointer;

	string command;
	char task;
	char choice;

	int idGamer;
	int mode; //режим: 1 - доступны настройки 2 - допступны во время игры

public:
	Facade(Gamer* gamer);
	void setTask(char task);
	void editMode(int mode, int idGamer);
	void checkListUnit();
	void listOptionUnit();
	void readerCommands();
	void shablonCommandUnit();
	void checkListBase();
	void listOptionBase();
	void shablonCommandBase();
	~Facade();
	void design();
};