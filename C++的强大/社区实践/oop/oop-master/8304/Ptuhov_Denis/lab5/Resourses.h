#pragma once
#include <string>

enum class EffectTypes : int
{
	damage,
	hp,
	range
};

struct LandscapeInfo
{
	int how_much = 0;
	EffectTypes what = EffectTypes::hp;
};

struct Hp
{
	Hp() = default;

	void decrease(int n);
	void increase(int n);
	int& get();

private:
	int hp = 0;
};

struct Damage
{
	Damage() = default;

	void decrease(int n);
	void increase(int n);
	int& get();

private:
	int damage = 0;
};

struct Point
{
	int x;
	int y;

	bool operator==(Point& p2)
	{
		return x == p2.x && y == p2.y;
	}
};

enum class takeDamageResult : int
{
	damageTaken,
	block,
	dodge,
	death
};

enum class addAndRemoveResult : int
{
	addErrorColission,
	addErrorIncorrectCoord,
	removeErrorIncorrectCoord,
	removeErrorNoUnit,
	MaxUnitsCntError,
	unitAdded,
	unitRemoved
};

enum class moveResult : int
{
	moveComplete,
	moveCoordinateError
};

enum class maxUnitsCntResult : int
{
	incorrectData,
	dataCorrect
};

enum class shootResult : int
{
	hit,
	miss
};

enum class LandscapeTypes : int
{
	ground,
	mountain,
	swamp
};

struct NtrlObjEffect
{
	int how_much = 0;
	EffectTypes what;
};


enum class BaseMUCResult : int
{
	incorrectData,
	alreadyBigger,
	correct
};

enum class LogTypes : int
{
	File,
	Terminal,
	No
};

struct SaveFile
{
	std::string name;
	bool is_used = false;
};