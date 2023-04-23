#pragma once
#include <fstream>
#include "Field.h"
#include <string>
#include <iostream>
#include "BitingZombyFactory.h"
#include "HumanOnBikeFactory.h"
#include "HumanOnCarFactory.h"
#include "HumanWithBatFactory.h"
#include "HumanWithGrenadeFactory.h"
#include "HumanWithGunFactory.h"
#include "HumanWithSwordFactory.h"
#include "KamikadzeZombyFactory.h"
#include "SpitToAreaZombyFactory.h"
#include "SpitToEnemyZombyFactory.h"
#include "StinkyZombyFactory.h"
#include "StrongZombyFactory.h"
#include "LargeArmorObject.h"
#include "LargeMedicine.h"
#include "SmallArmorObject.h"
#include "SmallMedicine.h"
#include "gamemode.h"
#include "state.h"
#include "towersettingstate.h"
#include "unitsettingstate.h"


class Loader
{
private:
	std::ifstream file;
	std::shared_ptr<Field> field;
	std::shared_ptr<Mediator> mediator;

	void setLastCell(int x, int y);
	void setCell(int x, int y);
	std::shared_ptr<Land> getLand();
	std::shared_ptr<Tower> getTower();
	std::shared_ptr<Unit> getUnit();
	std::shared_ptr<NeutralObject> getObj();
public:
    Loader();
    void setMediator(std::shared_ptr<Mediator> mediator);
	~Loader();
    std::shared_ptr<Field> loadField();
    GameMode loadGameMode();
    size_t loadStepNumber();
    std::shared_ptr<State> loadState();
};

