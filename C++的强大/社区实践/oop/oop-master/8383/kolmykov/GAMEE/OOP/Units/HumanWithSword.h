#pragma once
#include "MeleeHuman.h"
#include "SwordAttack.h"
#include "Sword.h"


class HumanWithSword :
	public MeleeHuman
{
public:
	HumanWithSword();
    HumanWithSword(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	HumanWithSword(int x, int y, int level);
	HumanWithSword(const HumanWithSword& other);
	HumanWithSword(HumanWithSword&& other);
	HumanWithSword& operator=(const HumanWithSword& other);
	HumanWithSword& operator=(HumanWithSword&& other);
	~HumanWithSword();
	char getChar();
    std::string getPath();
};

