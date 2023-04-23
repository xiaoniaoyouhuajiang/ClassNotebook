#pragma once
#include "RangeHuman.h"
#include "GrenadeAttack.h"
#include "Grenade.h"


class HumanWithGrenade :
	public RangeHuman
{
public:
	HumanWithGrenade();
    HumanWithGrenade(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	HumanWithGrenade(const HumanWithGrenade& other);
	HumanWithGrenade(int x, int y, int level);
	HumanWithGrenade(HumanWithGrenade&& other);
	HumanWithGrenade& operator=(const HumanWithGrenade& other);
	HumanWithGrenade& operator=(HumanWithGrenade&& other);
	~HumanWithGrenade();
	char getChar();
    std::string getPath();
};

