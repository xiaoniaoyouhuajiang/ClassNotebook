#pragma once
#include "HumanOnMachine.h"
#include "CarAttack.h"
#include "CarMove.h"
#include "Bat.h"


class HumanOnCar :
	public HumanOnMachine
{
public:
	HumanOnCar();
    HumanOnCar(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	HumanOnCar(int x, int y, int level);
	HumanOnCar(const HumanOnCar& other);
	HumanOnCar(HumanOnCar&& other);
	HumanOnCar& operator=(const HumanOnCar& other);
	HumanOnCar& operator=(HumanOnCar&& other);
	~HumanOnCar();
	char getChar();
    std::string getPath();
};

