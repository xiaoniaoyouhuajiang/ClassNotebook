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
    virtual int relocate(int x, int y, GameField& board, int size);
    virtual int atack(int cell1, int cell2, GameField& board);
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
    int atack(int cell1, int cell2, GameField &board);
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
    int relocate(int x, int y, GameField& board, int size);
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
    int relocate(int x, int y, GameField& board, int size);
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
    int relocate(int x, int y, GameField &board, int size);
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
    int atack(int cell1, int cell2, GameField &board);
};


class Buffer : public Unit {
public:
	void buff(int x, int y, GameField& board);
    int relocate(int x, int y, GameField& board, int size);
	Buffer();
	~Buffer();
};


//DEFEND UNITS-----------------------------------------------//

class Wall :public Unit {
public:
    int atack(int cell1, int cell2, GameField &board);
	Wall();
	~Wall();
};

class ImmortalWall : public Unit {
public:
	int liveTime;
    int atack(int cell1, int cell2, GameField &board);
	ImmortalWall();
	~ImmortalWall();
};


class HealTower : public Unit {
public:
	int heal;
    void towerHeal(int cell, GameField& board);
	HealTower();
	~HealTower();
};


class HealUnit : public Unit {
public:
    void unitHeal(int cell, GameField& board);
	int heal;
	HealUnit();
	~HealUnit();
};

class Pudge : public Unit {
public:
    int hook(int x, int y, GameField& board);
	Pudge();
	~Pudge();
};


class Comander : public Unit {
public:
    void increase(int x, int y, GameField& board);
	void poising(int x, int y, GameField& board);
    int relocate(int x, int y, GameField& board, int size);
	Comander();
	~Comander();
};
