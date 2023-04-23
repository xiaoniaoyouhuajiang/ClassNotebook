#pragma once
#include "Human.h"
#include "HeavyArmor.h"
class HumanOnMachine :
	public Human
{
public:
	HumanOnMachine();
    HumanOnMachine(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	HumanOnMachine(int x, int y, int level);
	HumanOnMachine(const HumanOnMachine& other);
	HumanOnMachine(HumanOnMachine&& other);
	HumanOnMachine& operator=(const HumanOnMachine& other);
	HumanOnMachine& operator=(HumanOnMachine&& other);
	virtual ~HumanOnMachine();
	virtual char getChar();
};
