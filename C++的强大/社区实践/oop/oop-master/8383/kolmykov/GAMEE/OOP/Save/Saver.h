#pragma once
#include "Field.h"
#include <fstream>
#include "TowerSnapshot.h"
#include "UnitSnapshot.h"
#include "ObjectSnapshot.h"
#include "gamemode.h"
#include "state.h"


class Saver
{
private:
    GameMode mode;
    int stepNumber;
	std::shared_ptr<Field> field;
    std::shared_ptr<State> state;
	std::ofstream file;
	void writeLastCell(int x, int y);
	void writeCell(int x, int y);
	void saveLand(std::shared_ptr<Land> land);
	void saveTower(std::shared_ptr<Tower> tower);
	void saveUnit(std::shared_ptr<Unit> unit);
	void saveObject(std::shared_ptr<NeutralObject> object);
    void saveField();
    void saveModeAndNumber();
    void saveState();
public:
    Saver(GameMode mode, size_t stepNumber, std::shared_ptr<Field> field, std::shared_ptr<State> state);
	~Saver();
	void save();
};

