#include "Mediator.h"
#include "Field.h"
#include "Tower.h"
#include "Unit.h"
#include "NeutralObject.h"
#include "LogerAdapter.h"


Mediator::Mediator(std::shared_ptr<Field> field) {
	this->field = field;
}

Mediator::Mediator()
{
}


Mediator::~Mediator() {

}

void Mediator::setField(std::shared_ptr<Field> field)
{
	this->field = field;
}

void Mediator::reactOnUnitMove(int x, int y, std::shared_ptr<Unit> unit) {
	int currY = unit->getY();
	switch (unit->getKind()) {
	case HUMAN:
        for (int i = currY - 1; i >= y; i--) {
            if (i >= 0 && i < field->getHeight()) {
                if (!field->getCell(x, i)->hasUnit() && !field->getCell(x, i)->hasTower()) {
                    currY = i;
					if (field->getCell(x, i)->hasObj()) {
						field->getCell(x, i)->getObj()->affectOnUnit(unit);
                        field->getCell(x, i)->setObj(nullptr);
					}

				}
                else {
                    break;
                }
			}
		}
        if (unit->getY() != currY) {
            field->getCell(x, currY)->setUnit(unit);
            field->getCell(x, unit->getY())->setUnit(nullptr);
            unit->setY(currY);
            field->getCell(x, currY)->getLand()->bufUnit(unit);
            loger->logAboutUnitMove(x, currY);
            if (currY == 0) {
                unit->notifyAboutKill();
                unit->notifyObservers();
                field->getCell(x, currY)->setUnit(nullptr);
            }
        }
		field->printField();
		return;
	case ZOMBY:
        for (int i = currY + 1; i <= y; i++) {
            if (i >= 0 && i < field->getHeight()) {
                if (!field->getCell(x, i)->hasUnit() && !field->getCell(x, i)->hasTower()) {
                    currY = i;
					if (field->getCell(x, i)->hasObj()) {
						field->getCell(x, i)->getObj()->affectOnUnit(unit);
                        field->getCell(x, i)->setObj(nullptr);
					}
				}
                else {
                    break;
                }
			}
		}
        if(unit->getY() != currY) {
            field->getCell(x, currY)->setUnit(unit);
            field->getCell(x, unit->getY())->setUnit(nullptr);
            unit->setY(currY);
            field->getCell(x, currY)->getLand()->bufUnit(unit);
            loger->logAboutUnitMove(x, currY);
            if (currY == field->getHeight() - 1) {
                unit->notifyAboutKill();
                unit->notifyObservers();
                field->getCell(x, currY)->setUnit(nullptr);
            }
        }
		field->printField();
		return;
	default:
		break;
	}
	std::cout << "\nДвигаться некуда\n";
}

void Mediator::reactOnUnitAttack(int damage, std::shared_ptr<Unit> unit, std::vector<Point>& points, bool isSigleAttack) {
	for (int i = 0; i < points.size(); i++) {
		if (points[i].x >= 0 && points[i].x < field->getWidth() && points[i].y >= 0 && points[i].y < field->getHeight()) {
			std::shared_ptr<FieldCell> target = field->getCell(points[i].x, points[i].y);
			if (target->getUnit() != nullptr && target->getUnit()->getKind() != unit->getKind()) {
				target->getUnit()->damageUnit(damage);
				loger->logAboutUnitAttack(unit->getX(), unit->getY());
				loger->logAboutUnitDamage(points[i].x, points[i].y, unit->getOwnDamage() + unit->getLandDamage() + unit->getWeapon()->getDamage());
				if (target->getUnit()->getHP() <= 0) {
					loger->logAboutUnitDeath(points[i].x, points[i].y);
					target->getUnit()->notifyObservers();
					target->setUnit(nullptr);
					unit->notifyAboutKill();
					field->printField();
				}
				else {
					loger->logUnitStatus(target->getUnit());
				}
				if (isSigleAttack) {
					break;
				}
			}
			else if (target->getTower() != nullptr){
				loger->logAboutUnitAttack(unit->getX(), unit->getY());
				loger->logAboutTowerDamage(points[i].x, points[i].y, unit->getOwnDamage() + unit->getLandDamage() + unit->getWeapon()->getDamage());
				target->getTower()->damageTower(damage);
				if (target->getTower()->getHP() <= 0) {
					loger->logAboutTowerDeath(points[i].x, points[i].y);
					target->setTower(nullptr);
					unit->notifyAboutKill();
					field->printField();
				}
				else {
					loger->logTowerStatus(target->getTower());
				}
				if (isSigleAttack) {
					break;
				}
			}
		}
	}
}

void Mediator::reactOnTowerAttack(std::shared_ptr<Tower> tower)
{
	if (tower->getY() > 0) {
		if (field->getCell(tower->getX(), tower->getY() - 1)->hasUnit()) {
            std::shared_ptr<Unit> unit = field->getCell(tower->getX(), tower->getY() - 1)->getUnit();
            if (unit->getKind() != tower->getKind()) {
                unit->damageUnit(tower->getDamage());
                if (unit->getHP() <= 0) {
                    reactOnUnitDeath(unit);
                }
            }
		}
	}
	if (tower->getY() < field->getHeight() - 1) {
		if (field->getCell(tower->getX(), tower->getY() + 1)->hasUnit()) {
            std::shared_ptr<Unit> unit = field->getCell(tower->getX(), tower->getY() + 1)->getUnit();
            if (unit->getKind() != tower->getKind()) {
                unit->damageUnit(tower->getDamage());
                if (unit->getHP() <= 0) {
                    reactOnUnitDeath(unit);
                }
            }
		}
	}
}

std::shared_ptr<LogerAdapter> Mediator::getLoger()
{
	return loger;
}

void Mediator::setLoger(std::shared_ptr<LogerAdapter> loger)
{
	this->loger = loger;
}


void Mediator::reactOnUnitDeath(std::shared_ptr<Unit> unit) {
    getLoger()->logAboutUnitDeath(unit->getX(), unit->getY());
    unit->notifyObservers();
    field->getCell(unit->getX(), unit->getY())->setUnit(nullptr);
    field->printField();
}
