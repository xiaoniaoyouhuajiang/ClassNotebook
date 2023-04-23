#pragma once
#include "HumanOnMachine.h"
#include "BikeAttack.h"
#include "BikeMove.h"
#include "Bat.h"


class HumanOnBike :
	public HumanOnMachine
{
public:
	HumanOnBike();
    HumanOnBike(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	HumanOnBike(int x, int y, int level);
	HumanOnBike(const HumanOnBike& other);
	HumanOnBike(HumanOnBike&& other);
	HumanOnBike& operator=(const HumanOnBike& other);
	HumanOnBike& operator=(HumanOnBike&& other);
	~HumanOnBike();
	char getChar();
    std::string getPath();
};

