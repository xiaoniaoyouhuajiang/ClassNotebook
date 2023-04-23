#pragma once
#include "MeleeHuman.h"
#include "AttackWithBat.h"
#include "Bat.h"


class HumanWithBat :
	public MeleeHuman
{
public:
	HumanWithBat();
    HumanWithBat(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	HumanWithBat(int x, int y, int level);
	HumanWithBat(const HumanWithBat& other);
	HumanWithBat(HumanWithBat&& other);
	HumanWithBat& operator=(const HumanWithBat& other);
	HumanWithBat& operator=(HumanWithBat&& other);
	~HumanWithBat();
	char getChar();
    std::string getPath();
};

