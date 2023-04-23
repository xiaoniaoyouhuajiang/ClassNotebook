#pragma once
#include "RangeHuman.h"
#include  "GunAttack.h"
#include "Pistol.h"


class HumanWithGun :
	public RangeHuman
{
public:
	HumanWithGun();
    HumanWithGun(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	HumanWithGun(int x, int y, int level);
	HumanWithGun(const HumanWithGun& other);
	HumanWithGun(HumanWithGun&& other);
	HumanWithGun& operator=(const HumanWithGun& other);
	HumanWithGun& operator=(HumanWithGun&& other);
	~HumanWithGun();
	char getChar();
    std::string getPath();
};

