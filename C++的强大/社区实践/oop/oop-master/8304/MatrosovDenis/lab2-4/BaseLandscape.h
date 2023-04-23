#pragma once
#include <cstdlib>
#include <time.h>
/*
##########################################
Èíòåğôåéñ äëÿ ëàíäøàôòà
##########################################
*/
class BaseLandscape
{
public:
	BaseLandscape() {
		passable = true;
		assaulter = true;
		attacked = true;
		HpModifier = 0;
		AttackRangeModifier = 0;
		MoveRangeModifier = 0;
		AttackÑoefficient = 1;
		id = 0;
	}
	~BaseLandscape(){}

	const int HpMod() {
		return HpModifier;
	}
	const int AttackRangeMod() {
		return AttackRangeModifier;
	}
	const int MoveRangeMod() {
		return MoveRangeModifier;
	}
	int RecalculateDamage(int Damage) {
		return int(double(Damage) * AttackÑoefficient);
	}
	int ID() {
		return id;
	}
	bool is_passable() {
		return passable;
	}
	bool is_touchable() {
		return attacked;
	}
	bool is_assaulter() {
		return assaulter;
	}

protected:
	int id;
	bool passable;
	bool assaulter;
	bool attacked;
	int HpModifier;
	int AttackRangeModifier;
	int MoveRangeModifier;
	double AttackÑoefficient;
};


/*
##########################################
Òèïû ëàíøàôòà
##########################################
*/

class Water_obstacle : public BaseLandscape
{
public:
	Water_obstacle() {
		passable = false;
		assaulter = false;
		attacked = false;
		HpModifier = 0;
		AttackRangeModifier = 0;
		MoveRangeModifier = 0;
		AttackÑoefficient = 1;
		id = 1;
	}
	~Water_obstacle(){}

private:

};

class Mountain : public BaseLandscape
{
public:
	Mountain() {
		passable = true;
		assaulter = true;
		attacked = false;
		HpModifier = 0;
		AttackRangeModifier = 1;
		MoveRangeModifier = -1;
		AttackÑoefficient = 0.8;
		id = 2;
	}
	~Mountain() {}

private:

};

class Steppes : public BaseLandscape
{
public:
	Steppes() {
		passable = true;
		assaulter = true;
		attacked = true;
		HpModifier = 10;
		AttackRangeModifier = 0;
		MoveRangeModifier = 1;
		AttackÑoefficient = 1;
		id = 3;
	}
	~Steppes() {}

private:

};

class Swamp : public BaseLandscape
{
public:
	Swamp() {
		passable = true;
		assaulter = true;
		attacked = true;
		HpModifier = -20;
		AttackRangeModifier = 0;
		MoveRangeModifier = -2;
		AttackÑoefficient = 0.5;
		id = 4;
	}
	~Swamp() {}

private:

};


/*
##########################################
Õğàíèëèùå äëÿ ëàíäøàôòà
##########################################
*/

class LandscapeComposite
{
public:
	LandscapeComposite(int x, int y);
	LandscapeComposite(const LandscapeComposite& copy);
	~LandscapeComposite();
	size_t getX() {
		return X_SIZE;
	}
	size_t getY() {
		return Y_SIZE;
	}
	BaseLandscape getLandscape(int x, int y) {
		return Landscape[x][y];
	}

	BaseLandscape* checkLand(int x, int y) {
		if (x < X_SIZE && y < Y_SIZE) {
			return &Landscape[x][y];
		}
		return nullptr;
	}

	void GenerateLandscape();
	void PrintLAndscape();
private:
	BaseLandscape** Landscape;
	size_t X_SIZE;
	size_t Y_SIZE;
};
