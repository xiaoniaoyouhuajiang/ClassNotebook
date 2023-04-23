#pragma once
#include <vector>
#include <map>
//#include "Unit.h"
#include "Field.h"
#include "ProxyLog.h"
#include "Memento.h"

enum class UnitTypes;

class Field;
class Unit;
class Memento;
class Base {

	int hp;

	int x;
	int y;

	//std::vector<Unit*> units;
	std::map<int, Unit*> units;
	int lastId;
	int unitsCounter;
	Field* parentField;
	ProxyLog* log;
	int player;
	int money = 10;
	int turn = 1;
public:
	Base(int player = 1);
	~Base();
	
	Field* getParentField();
	void setParentField(Field*& field);

	void setBase(int x, int y);
	int getPlayer();
	int getX();
	int getY();
	int getTurn();
	void addTurn();

	void setHp(int val);
	void setMoney(int val);
	int getMoney();
	Unit* getUnit(int id);
	int getHp();

	void writeBaseState();
	bool writeUnitInfo(int id);//true если успешно

	Unit* createAndSetUnit(UnitTypes type, int lvl, int x=0, int y=0);
	void deleteUnit(Unit*& unit);
	void deleteUnits();
	std::map<int, Unit*>::iterator deleteUnit(std::map<int, Unit*>::iterator it);

	void addLog(ProxyLog* log);
	bool tryToDie();
	void prepareToNextTurn();

	void fillMemento(Memento*& snapshot, bool myTurn = false);
	void newBase(Memento*& snapshot, int myNum);
};

