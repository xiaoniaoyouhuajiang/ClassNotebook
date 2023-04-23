#pragma once
#include "FatZomby.h"
#include "NoArmor.h"
#include "BlowingUpAttackBehavior.h"
#include "BlowingUpHead.h"


class KamikadzeZomby :
	public FatZomby
{
public:
	KamikadzeZomby();
    KamikadzeZomby(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep);
	KamikadzeZomby(int x, int y, int level);
	KamikadzeZomby(const KamikadzeZomby& other);
	KamikadzeZomby(KamikadzeZomby&& other);
	KamikadzeZomby& operator=(const KamikadzeZomby& other);
	KamikadzeZomby& operator=(KamikadzeZomby&& other);
	~KamikadzeZomby();
	char getChar();
    std::string getPath();
};

