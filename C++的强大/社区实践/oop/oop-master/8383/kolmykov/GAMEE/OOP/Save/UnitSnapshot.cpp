

#include "UnitSnapshot.h"



UnitSnapshot::UnitSnapshot(UnitType type, int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, size_t lastStep)
    : type(type), hp(hp), maxHP(maxHP), ownArmor(ownArmor), ownDamage(ownDamage), visability(visability), level(level), landDamage(landDamage), landDefence(landDefence), observers(observers), observerSize(observerSize), observerCount(observerCount), coordX(coordX), coordY(coordY), lastStep(lastStep)
{

}


UnitSnapshot::~UnitSnapshot()
{
}

int UnitSnapshot::getType()
{
	return type;
}

int UnitSnapshot::getHP()
{
	return hp;
}

int UnitSnapshot::getMaxHP()
{
	return maxHP;
}

int UnitSnapshot::getOwnArmor()
{
	return ownArmor;
}

int UnitSnapshot::getOwnDamage()
{
	return ownDamage;
}

bool UnitSnapshot::getVisability()
{
	return visability;
}

int UnitSnapshot::getLevel()
{
	return level;
}

int UnitSnapshot::getLandDamage()
{
	return landDamage;
}

int UnitSnapshot::getLandDefence()
{
	return landDefence;
}

std::shared_ptr<std::shared_ptr<ObserverInterface>[]> UnitSnapshot::getObservers()
{
	return observers;
}

int UnitSnapshot::getObserverSize()
{
	return observerSize;
}

int UnitSnapshot::getObserverCount()
{
	return observerCount;
}

int UnitSnapshot::getCoordX()
{
	return coordX;
}

int UnitSnapshot::getCoordY()
{
	return coordY;
}

size_t UnitSnapshot::getLastStep() {
    return lastStep;
}
