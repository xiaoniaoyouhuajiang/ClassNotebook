#pragma once
#include "stdafx.h"
#include <memory>

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

protected:

	int MaxHp;
	int Hp;
	int MoveDistance;
	int Armor;
	int AttackDistance;
	int Damage;

	Jobs Job;

	void GetDamage(int damage);


};

/*
######################################################
Классы юнитов конницы
######################################################
*/

class Cavalry: public BaseUnit
{
public:
	Cavalry(int x, int y, Factions f);
	Cavalry(const Cavalry& copy);
	~Cavalry();

	Cavalry& operator=(const Cavalry& copy);
	
private:

};

class Knight: public BaseUnit
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

class Warrior : public BaseUnit
{
public:
	Warrior(int x, int y, Factions f);
	Warrior(const Warrior& copy);
	~Warrior();

	Warrior& operator=(const Warrior& copy);
	
private:

};

class Piker : public BaseUnit
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

class Archer : public BaseUnit
{
public:
	Archer(int x, int y, Factions f);
	Archer(const Archer& copy);
	~Archer();

	Archer& operator=(const Archer& copy);
	
private:

};

class Arbalester : public BaseUnit
{
public:
	Arbalester(int x, int y, Factions f);
	Arbalester(const Arbalester& copy);
	~Arbalester();

	Arbalester& operator=(const Arbalester& copy);
	
private:

};