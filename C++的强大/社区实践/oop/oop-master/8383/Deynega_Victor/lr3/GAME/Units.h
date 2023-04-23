#pragma once
#include "GameField.h"
#include "Neutral.h"
//#include "Base.h"

class Unit {
public:
	int locateCost;
	int x;
	int y;
	int damage;
	int health;
	int type;
	int index;
	virtual void castFor();
	bool relocate(int x, int y, GameField& board, int size);
	Unit();
	~Unit();
};

class LongRangeUnits : public Unit {
public:
	int reLocateCost;
	int levelUpCost;
	int targetX;
	int targetY;
	bool didShoot;	
	LongRangeUnits();
	~LongRangeUnits();
	bool makeShot(int x, int y, GameField& board, int dmg);
};

class FarmUnits : public Unit{
public:
	int reLocateCost;
	int levelUpCost;
	int moneyPerTurn;
	FarmUnits();
	~FarmUnits();
};

class MeleeUnits : public Unit{
public:
	MeleeUnits();
	~MeleeUnits();
};

class Archer : public LongRangeUnits{
public:
	Archer();
	
	Archer(int x, int y); //remove
	~Archer();
};

class Ballista : public LongRangeUnits {
public:
	Ballista();
	
	Ballista(int x, int y); //remove
	~Ballista();
};

class DefendFarmUnit : public FarmUnits {
public:
	DefendFarmUnit(); 
	
	DefendFarmUnit(int x, int y); //remove
	~DefendFarmUnit();
};

class AttackFarmUnit : public FarmUnits {
public:
	
	AttackFarmUnit();
	AttackFarmUnit(int x, int y); //remove
	~AttackFarmUnit();
};
 
class SuicideBomber : public MeleeUnits {
public:
	SuicideBomber();
	
	SuicideBomber(int x, int y); //remove
	~SuicideBomber();
};

class SuicideBomberGeneral : public MeleeUnits {
public:
	
	SuicideBomberGeneral(int x, int y); //remove
	SuicideBomberGeneral();
	~SuicideBomberGeneral();
};

class Objector {
public:
	NeutralObject* p;
	Objector(NeutralObject* ptr);
	Objector();
	~Objector();
	friend void operator+(Objector obj, Unit& someUnit);
};