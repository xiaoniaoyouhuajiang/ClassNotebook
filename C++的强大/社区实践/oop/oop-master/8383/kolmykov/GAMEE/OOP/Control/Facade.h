#pragma once
#include "Kind.h"
#include "UnitFactory.h"
#include "UnitExistenceHandler.h"
#include "FinalMoveHandler.h"
#include "FinalAttackHandler.h"
#include "TowerExistenceHandler.h"
#include "TowerPosibilityHandler.h"
#include "FreeCellForUnitHandler.h"
#include "FinalCreateUnitHandler.h"
#include "freeCellForTowerHandler.h"
#include "FinalSetTowerHandler.h"


class Facade
{
protected:
	Kind kind;
	std::shared_ptr<Request> request;
	std::shared_ptr<Field> field;
	std::shared_ptr<Handler> unitExistenceHandlerForMove;
	std::shared_ptr<Handler> unitExistenceHandlerForAttack;
	std::shared_ptr<Handler> towerExistenceHandler;
	std::shared_ptr<Handler> freeCellForTowerHandler;
public:
	Facade(Kind kind, std::shared_ptr<Field> field);
	~Facade();
	void move(int x, int y);
	void attack(int x, int y);
	void create(int xT, int yT, int xU, int yU);
	void setTower(int x, int y, std::shared_ptr<UnitFactory> factory);
	void endStep();
};

