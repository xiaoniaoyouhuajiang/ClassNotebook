#pragma once //check
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
	virtual void castFor();
	bool relocate(int x, int y, GameField& board, int size);
	std::string getName();
	friend  std::ostream& operator<<(std::ostream& out, Unit& unit);
	Unit();
	~Unit();
};

class LongRangeUnits : public Unit {
public:
	int reLocateCost;
	int levelUpCost;
	int targetX; //??
	int targetY; //??
	bool didShoot;	
	LongRangeUnits();
	~LongRangeUnits();
	bool makeShot(int newx, int newy, GameField& board, int dmg);
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


class Assasin :public Unit {
public:
	Assasin();
	~Assasin();
	void attack(int x, int y, GameField& board);
};


class Buffer : public Unit {
public:
	void buff(int x, int y, GameField& board);
	Buffer();
	~Buffer();
};


//DEFEND UNITS-----------------------------------------------//

class Wall :public Unit {
public:
	bool relocate(int x, int y, GameField& board, int size);
	Wall();
	~Wall();
};

class ImmortalWall : public Unit {
public:
	int liveTime;
	bool relocate(int x, int y, GameField& board, int size);
	ImmortalWall();
	~ImmortalWall();
};


class HealTower : public Unit {
public:
	int heal;
	HealTower();
	~HealTower();
};


class HealUnit : public Unit {
public:
	int heal;
	HealUnit();
	~HealUnit();
};

class Pudge : public Unit {
public:
	void hook(int x, int y, GameField& board);
	Pudge();
	~Pudge();
};


class Comander : public Unit {
public:
	void increase(GameField& board);
	void poising(int x, int y, GameField& board);
	Comander();
	~Comander();
};