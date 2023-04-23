#include "Facade.h"
#include "LogerAdapter.h"


Facade::Facade(Kind kind, std::shared_ptr<Field> field) {
	this->kind = kind;
	this->field = field;
	request = std::shared_ptr<Request>(new Request());
	request->kind = kind;
	unitExistenceHandlerForMove = std::shared_ptr<Handler>(new UnitExistenceHandler(field));
	unitExistenceHandlerForMove->setNextHandler(std::shared_ptr<Handler>(new FinalMoveHandler(field)));
	unitExistenceHandlerForAttack = std::shared_ptr<Handler>(new UnitExistenceHandler(field));
	unitExistenceHandlerForAttack->setNextHandler(std::shared_ptr<Handler>(new FinalAttackHandler(field)));
	towerExistenceHandler = std::shared_ptr<Handler>(new TowerExistenceHandler(field));
	towerExistenceHandler->setNextHandler(std::shared_ptr<Handler>(new TowerPosibilityHandler(field)));
	towerExistenceHandler->getNextHandler()->setNextHandler(std::shared_ptr<Handler>(new FreeCellForUnitHandler(field)));
	towerExistenceHandler->getNextHandler()->getNextHandler()->setNextHandler(std::shared_ptr<Handler>(new FinalCreateUnitHandler(field)));
	freeCellForTowerHandler = std::shared_ptr<Handler>(new FreeCellForTowerHandler(field));
	freeCellForTowerHandler->setNextHandler(std::shared_ptr<Handler>(new FinalSetTowerHandler(field)));
}


Facade::~Facade()
{
}

void Facade::move(int x, int y) {
	field->getMediator()->getLoger()->logAboutUserMove(x, y);
	request->coordX1 = x;
	request->coordY1 = y;
	unitExistenceHandlerForMove->handle(request);
}

void Facade::attack(int x, int y) {
	field->getMediator()->getLoger()->logAboutUserAttack(x, y);
	request->coordX1 = x;
	request->coordY1 = y;
	unitExistenceHandlerForAttack->handle(request);
}

void Facade::create(int xT, int yT, int xU, int yU) {
	field->getMediator()->getLoger()->logAboutUserCreateUnit(xT, yT, xU, yU);
	request->coordX1 = xT;
	request->coordX2 = xU;
	request->coordY1 = yT;
	request->coordY2 = yU;
	towerExistenceHandler->handle(request);
}

void Facade::setTower(int x, int y, std::shared_ptr<UnitFactory> factory) {
	field->getMediator()->getLoger()->logAboutUserSettingTower(x, y);
	request->coordX1 = x;
	request->coordY1 = y;
	request->factory = factory;
	freeCellForTowerHandler->handle(request);
}

void Facade::endStep() {
	field->getMediator()->getLoger()->logAboutEndOfStep();
	//TODO
}
