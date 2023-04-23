#pragma once
//#include "Field.h"
#include "IUnit.h"
#include <string>
#include "ProxyLog.h"
class Field;
class Base;
enum class UnitTypes {
	MELEE, RANGE, HORSEMAN
};
//enum class UnitTypes;
class Unit: public IUnit {

	int x;
	int y;
	Field*  parentField;
	Base* parentBase;
	int player;
	int id;

	int attack;
	int hp;
	int armor;
	int haste;
	int range;
	int level;
	int cost;
	UnitTypes type;

	int attackDebuff;
	int armorBuff;
	int attackBuff;
	int rangeBuff;

	ProxyLog* log;

	bool attacked = false;
	bool moved = false;
public:

	Unit() :x(-1), y(-1), parentField(nullptr),parentBase(nullptr), attackDebuff(0), armorBuff(0), attackBuff(0){};
	~Unit();

	int getId();
	
	int getPlayer();

	int getAttack();
	int getHp();
	int getArmor();
	int getHaste();
	int getRange();
	int getLevel();
	int getCost();
	UnitTypes getUnitType();

	int getAttackDebuff();
	int getArmorBuff();
	int getAttackBuff();
	int getRangeBuff();


	bool getAttacked();
	bool getMoved();

	Field* getParentField();
	int getX();
	int getY();
	std::string getUnitName();

	void setId(int val);

	void setAttack(int val);
	void setHp(int val);
	void setArmor(int val);
	void setHaste(int val);
	void setRange(int val);
	void setLevel(int val);
	void setCost(int val);
	void setUnitType(UnitTypes val);

	void setAttackDebuff(int val);
	void setArmorBuff(int val);
	void setAttackBuff(int val);
	void setRangeBuff(int val);

	void resetAttacked();
	void resetMoved();

	void setAttacked(bool val);
	void setMoved(bool val);

	void setParentField(Field *& field);
	void setParentBase(Base*& base, int player);
	void addLog(ProxyLog* log);
	virtual bool tryToDie(Unit*& unit);
	virtual bool doAttack(Unit*& target);
	virtual void doMove(int x, int y);
	bool doAttackOnBase(Base*& target);
};

