#pragma once
#include "LogerProxy.h"
#include "UserMoveMessage.h"
#include "UserAttackMessage.h"
#include "UserCreateUnitMessage.h"
#include "UserSetTowerMessage.h"
#include "EndStepMessage.h"
#include "HandlerNotExistMessage.h"
#include "HandlerTowerNotExistMessage.h"
#include "HandlerTowerPossibilityMessage.h"
#include "HandlerEngagedCellMessage.h"
#include "UnitCreateMessage.h"
#include "TowerCreateMessage.h"
#include "UnitMoveMessage.h"
#include "UnitAttackMessage.h"
#include "UnitGetDamageMessage.h"
#include "UnitDeathMessage.h"
#include "TowerDeathMessage.h"
#include "TowerDamageMessage.h"
#include "UnitStatusMessage.h"
#include "TowerStatusMessage.h"
class LogerAdapter
{
private:
	std::shared_ptr<LogerProxy> loger;
public:
	LogerAdapter(std::shared_ptr<LogerProxy> loger);
	~LogerAdapter();
	void setLoger(std::shared_ptr<LogerProxy> loger);
	void logAboutUserMove(int x, int y);
	void logAboutUserAttack(int x, int y);
	void logAboutUserCreateUnit(int xT, int yT, int xU, int yU);
	void logAboutUserSettingTower(int x, int y);
	void logAboutEndOfStep();
	void logAboutUnitNotExist();
	void logAboutTowerNotExist();
	void logAboutTowwerNotPossible();
	void logAboutCellIsEngaged();
	void logAboutCreatedUnit(int x, int y);
	void logAboutCreatedTower(int x, int y);
	void logAboutUnitMove(int x, int y);
	void logAboutUnitAttack(int x, int y);
	void logAboutUnitDamage(int x, int y, int damage);
	void logAboutUnitDeath(int x, int y);
	void logAboutTowerDeath(int x, int y);
	void logAboutTowerDamage(int x, int y, int damage);
	void logUnitStatus(std::shared_ptr<Unit> unit);
	void logTowerStatus(std::shared_ptr<Tower> tower);
};

