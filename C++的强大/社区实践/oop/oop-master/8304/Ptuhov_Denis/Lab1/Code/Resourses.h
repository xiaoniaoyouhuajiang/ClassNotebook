#pragma once

struct Hp
{
	Hp() = default;

	void decrease(size_t n);
	void increase(size_t n);
	size_t get();

private:
	size_t hp = 0;
};

struct Damage
{
	Damage() = default;

	void decrease(size_t n);
	void increase(size_t n);
	size_t get();

private:
	size_t damage = 0;
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
