#pragma once
#include "Unit.h"
class ZombyUnit :
	public Unit
{
public:
    ZombyUnit(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	ZombyUnit();
	ZombyUnit(int x, int y, int level);
	ZombyUnit(const ZombyUnit& other);
	ZombyUnit(ZombyUnit&& other);
	ZombyUnit& operator=(const ZombyUnit& other);
	ZombyUnit& operator=(ZombyUnit&& other);
	virtual ~ZombyUnit();
	virtual char getChar();
};

