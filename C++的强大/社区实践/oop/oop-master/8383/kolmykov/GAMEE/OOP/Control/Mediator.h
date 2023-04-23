#pragma once
#include "vector"
#include "Point.h"
#include <memory>


class Field;
class Tower;
class Unit;
class NeutralObject;
class LogerAdapter;


class Mediator
{
protected:
	std::shared_ptr<Field> field;
	std::vector<std::shared_ptr<Unit>> units;
	std::vector<std::shared_ptr<NeutralObject>> objects;
	std::vector<std::shared_ptr<Tower>> towers;
	std::shared_ptr<LogerAdapter> loger;

public:
	Mediator(std::shared_ptr<Field> field);
	Mediator();
	~Mediator();
	void  setField(std::shared_ptr<Field> field);
    void reactOnUnitDeath(std::shared_ptr<Unit> unit);
	void reactOnUnitMove(int x, int y, std::shared_ptr<Unit> unit);
	void reactOnUnitAttack(int damage, std::shared_ptr<Unit> unit, std::vector<Point>& points, bool isSigleAttack);
	void reactOnTowerAttack(std::shared_ptr<Tower> tower);
	std::shared_ptr<LogerAdapter>getLoger();
	void setLoger(std::shared_ptr<LogerAdapter> loger);
};

