#pragma once
#include "stdafx.h"
#include <memory>
#include <iostream>

/*
######################################################
Класс объекта (любой штуки в игре)
######################################################
*/

enum class ObjectTypes
{
	Unit,
	PlayableStructure,
	NonPlayableStructure
};

enum class Jobs
{
	Move,
	Attack,
	Standing
};

enum class Factions
{
	Player,
	Enemy,
	Neutral
};

class Object
{
public:
	Object();

	Object(const Object& copy); //конструктор копирования (конструктор перемещения не требуется, так как нет ссылочных типов данных внутри класса)

	~Object();

	Object& operator=(const Object& copy); //оператор копирования-присваивания (копирование-перемещение не требуется)

	int getX();
	int getY();
	Factions getFaction();
	ObjectTypes getType();

	void setX(int x);
	void setY(int y);
	void setFactions(Factions f);
	void setType(ObjectTypes t);

protected:

	Factions ObjectFactions;
	ObjectTypes Type;

	int X_CORD;
	int Y_CORD;

};

/*
######################################################
Класс базового юнита (может все и ничего одновременно)
######################################################
*/

class BaseUnit : public Object
{
public:
	BaseUnit(int x, int y, Factions f);
	BaseUnit(const BaseUnit& copy);
	BaseUnit();
	~BaseUnit();

	BaseUnit& operator=(const BaseUnit& copy);

	void Move(int x, int y);

	void Attack(std::shared_ptr<BaseUnit> target);

	void printStatistic();
	void strengthen(int armor) {
		Armor += armor;
	}
	void incMoveDistance() {
		MoveDistance++;
	}
	void incAttackDistance() {
		AttackDistance++;
	}
	const int HP() {
		return Hp;
	}
	void GetDamage(int damage);
	void Heal(int h) {
		Hp = (Hp + h);
		Hp = Hp = Hp % MaxHp;
	}
protected:

	int MaxHp;
	int Hp;
	int MoveDistance;
	int Armor;
	int AttackDistance;
	int Damage;

	Jobs Job;
};

/*
######################################################
Классы юнитов конницы
######################################################
*/
class MountUnit :public BaseUnit
{
public:
	MountUnit() {}
	~MountUnit() {}

private:

};

class Cavalry: public MountUnit
{
public:
	Cavalry(int x, int y, Factions f);
	Cavalry(const Cavalry& copy);
	~Cavalry();

	Cavalry& operator=(const Cavalry& copy);
	
private:

};

class Knight: public MountUnit
{
public:
	Knight(int x, int y, Factions f);
	Knight(const Knight& copy);
	~Knight();

	Knight& operator=(const Knight& copy);

private:

};



/*
######################################################
Классы юнитов пехоты
######################################################
*/

class MelleUnit :public BaseUnit
{
public:
	MelleUnit() {}
	~MelleUnit() {}

private:

};


class Warrior : public MelleUnit
{
public:
	Warrior(int x, int y, Factions f);
	Warrior(const Warrior& copy);
	~Warrior();

	Warrior& operator=(const Warrior& copy);
	
private:

};

class Piker : public MelleUnit
{
public:
	Piker(int x, int y, Factions f);
	Piker(const Piker& copy);
	~Piker();

	Piker& operator=(const Piker& copy);

private:

};

/*
######################################################
Классы юнитов дальнего боя
######################################################
*/

class longRangeUnit :public BaseUnit
{
public:
	longRangeUnit() {}
	~longRangeUnit() {}

private:

};


class Archer : public longRangeUnit
{
public:
	Archer(int x, int y, Factions f);
	Archer(const Archer& copy);
	~Archer();

	Archer& operator=(const Archer& copy);
	
private:

};

class Arbalester : public longRangeUnit
{
public:
	Arbalester(int x, int y, Factions f);
	Arbalester(const Arbalester& copy);
	~Arbalester();

	Arbalester& operator=(const Arbalester& copy);
	
private:

};

/*
######################################################
Абстрактная фабрика
######################################################
*/

class ArmyFactory
{
public:
	virtual MountUnit createMountUnit(int x, int y, Factions f) = 0;
	virtual MelleUnit createMelleUnit(int x, int y, Factions f) = 0;
	virtual longRangeUnit createLongaRangeUnit(int x, int y, Factions f) = 0;
	virtual ~ArmyFactory() {}
};

class ArmyFirstGradeLevel : public ArmyFactory
{
public:
	MountUnit createMountUnit(int x, int y, Factions f) {
		return Cavalry(x, y, f);
	}
	MelleUnit createMelleUnit(int x, int y, Factions f) {
		return Warrior(x, y, f);
	}
	longRangeUnit createLongaRangeUnit(int x, int y, Factions f) {
		return Archer(x, y, f);
	}
};

class ArmySecondGradeLevel : public ArmyFactory
{
public:
	MountUnit createMountUnit(int x, int y, Factions f) {
		return Knight(x, y, f);
	}
	MelleUnit createMelleUnit(int x, int y, Factions f) {
		return Piker(x, y, f);
	}
	longRangeUnit createLongaRangeUnit(int x, int y, Factions f) {
		return Arbalester(x, y, f);
	}
};

/*
###################################################
Посредник для базы
###################################################
*/

class MapStructure : public Object
{
public:
	bool Alive() { return true; };
	void getDamage( int damage);
protected:
};


/*
######################################################
Нейтральные объекты
######################################################
*/

class BaseNeutralObject:public Object
{
public:
	BaseNeutralObject() {
		X_CORD = -1;
		Y_CORD = -1;
		count_of_supply = 0;
	};
	BaseNeutralObject(int x, int y);
	~BaseNeutralObject();
	void interact(BaseUnit& unit) {};
	void print() {
		std::cout << X_CORD << " " << Y_CORD << " " << name << " Supply: " << count_of_supply << std::endl;
	}
protected:
	int count_of_supply;
	std::string name;
};

class MedicallStation:public BaseNeutralObject
{
public:
	MedicallStation(int x, int y);
	~MedicallStation();
	void interact(BaseUnit* unit);
protected:

};

class Stable :public BaseNeutralObject
{
public:
	Stable(int x, int y);
	~Stable();
	void interact(BaseUnit* unit);
protected:

};

class Forge :public BaseNeutralObject
{
public:
	Forge(int x, int y);
	~Forge();
	void interact(BaseUnit* unit);
protected:

};

class Wizards_tower :public BaseNeutralObject
{
public:
	Wizards_tower(int x, int y);
	~Wizards_tower();
	void interact(BaseUnit* unit);
protected:

};

class NeutralContainer
{
public:
	NeutralContainer(int x);
	~NeutralContainer();
	std::shared_ptr<BaseNeutralObject> getNObj(int x, int y);
	bool addNObj(BaseNeutralObject obj);
	void printAll() {
		for (int i = 0; i < count; i++) {
			objects[i].print();
		}
	}
private:
	BaseNeutralObject* objects;
	size_t count;
	size_t max_count;
};


class NeutralFactory
{
public:
	MedicallStation createMedicallStation(int x, int y) {
		return MedicallStation(x, y);
	}
	Stable createStable(int x, int y) {
		return Stable(x, y);
	}
	Forge createForge(int x, int y) {
		return Forge(x, y);
	}
	Wizards_tower createWizardsTower(int x, int y) {
		return Wizards_tower(x, y);
	}
	virtual ~NeutralFactory() {}
};