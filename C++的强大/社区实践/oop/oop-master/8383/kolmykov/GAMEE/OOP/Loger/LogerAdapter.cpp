#include "LogerAdapter.h"



LogerAdapter::LogerAdapter(std::shared_ptr<LogerProxy> loger) {
	this->loger = loger;
}


LogerAdapter::~LogerAdapter()
{
}

void LogerAdapter::setLoger(std::shared_ptr<LogerProxy> loger) {
	if (this->loger != nullptr && loger != nullptr) {
		loger->setLoger(this->loger->getLoger());
		this->loger = loger;
	}
}

void LogerAdapter::logAboutUserMove(int x, int y)
{
	loger->log(std::shared_ptr<UserMoveMessage> (new UserMoveMessage(x, y)));
}

void LogerAdapter::logAboutUserAttack(int x, int y)
{
	loger->log(std::shared_ptr<UserAttackMessage> (new UserAttackMessage(x, y)));
}

void LogerAdapter::logAboutUserCreateUnit(int xT, int yT, int xU, int yU)
{
	loger->log(std::shared_ptr<UserCreateUnitMessage>(new UserCreateUnitMessage(xT, yT, xU, yU)));
}

void LogerAdapter::logAboutUserSettingTower(int x, int y)
{
	loger->log(std::shared_ptr<UserSetTowerMessage>(new UserSetTowerMessage(x, y)));
}

void LogerAdapter::logAboutEndOfStep()
{
	loger->log(std::shared_ptr<EndStepMessage>(new EndStepMessage()));
}

void LogerAdapter::logAboutUnitNotExist()
{
	loger->log(std::shared_ptr<HandlerNotExistMessage>(new HandlerNotExistMessage()));
}

void LogerAdapter::logAboutTowerNotExist()
{
	loger->log(std::shared_ptr<HandlerTowerNotExistMessage>(new HandlerTowerNotExistMessage()));
}

void LogerAdapter::logAboutTowwerNotPossible()
{
	loger->log(std::shared_ptr<HandlerTowerPossibilityMessage>(new HandlerTowerPossibilityMessage()));
}

void LogerAdapter::logAboutCellIsEngaged() {
	loger->log(std::shared_ptr<HandlerEngagedCellMessage>(new HandlerEngagedCellMessage()));
}

void LogerAdapter::logAboutCreatedUnit(int x, int y) {
	loger->log(std::shared_ptr<UnitCreateMessage> (new UnitCreateMessage(x , y)));
}

void LogerAdapter::logAboutCreatedTower(int x, int y)
{
	loger->log(std::shared_ptr<TowerCreateMessage>(new TowerCreateMessage(x, y)));
}

void LogerAdapter::logAboutUnitMove(int x, int y)
{
	loger->log(std::shared_ptr<UnitMoveMessage>(new UnitMoveMessage(x, y)));
}

void LogerAdapter::logAboutUnitAttack(int x, int y)
{
	loger->log(std::shared_ptr<UnitAttackMessage> (new UnitAttackMessage(x, y)));
}

void LogerAdapter::logAboutUnitDamage(int x, int y, int damage)
{
	loger->log(std::shared_ptr<UnitGetDamageMessage> (new UnitGetDamageMessage(x, y, damage)));
}

void LogerAdapter::logAboutUnitDeath(int x, int y)
{
	loger->log(std::shared_ptr<UnitDeathMessage>(new UnitDeathMessage(x, y)));
}

void LogerAdapter::logAboutTowerDeath(int x, int y)
{
	loger->log(std::shared_ptr<TowerDeathMessage>(new TowerDeathMessage(x, y)));
}

void LogerAdapter::logAboutTowerDamage(int x, int y, int damage)
{
	loger->log(std::shared_ptr<TowerDamageMessage>(new TowerDamageMessage(x , y, damage)));
}

void LogerAdapter::logUnitStatus(std::shared_ptr<Unit> unit)
{
	loger->log(std::shared_ptr<UnitStatusMessage>(new UnitStatusMessage(unit)));
}

void LogerAdapter::logTowerStatus(std::shared_ptr<Tower> tower)
{
	loger->log(std::shared_ptr<TowerStatusMessage>(new TowerStatusMessage(tower)));
}
