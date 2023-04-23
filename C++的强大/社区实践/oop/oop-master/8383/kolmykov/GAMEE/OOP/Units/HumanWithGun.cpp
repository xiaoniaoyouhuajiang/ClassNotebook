#include "HumanWithGun.h"



HumanWithGun::HumanWithGun()
{
	attackBehavior = std::shared_ptr<AttackBehavior>(new GunAttack());
	weapon = std::shared_ptr<Weapon>(new Pistol());
	type = UnitType::HUMAN_WITH_GUN;
}

HumanWithGun::HumanWithGun(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep)
:RangeHuman(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep) {
	attackBehavior = std::shared_ptr<AttackBehavior>(new GunAttack());
	weapon = std::shared_ptr<Weapon>(new Pistol());
	type = UnitType::HUMAN_WITH_GUN;
}

HumanWithGun::HumanWithGun(int x, int y, int level): RangeHuman(x, y, level)
{
	attackBehavior = std::shared_ptr<AttackBehavior>(new GunAttack());
	weapon = std::shared_ptr<Weapon>(new Pistol());
	type = UnitType::HUMAN_WITH_GUN;
}

HumanWithGun::HumanWithGun(const HumanWithGun & other):RangeHuman(other)
{
}

HumanWithGun::HumanWithGun(HumanWithGun && other): RangeHuman(other)
{
}

HumanWithGun& HumanWithGun::operator=(const HumanWithGun & other)
{
	this->hp = other.hp;
	this->maxHP = other.maxHP;
	this->ownArmor = other.ownArmor;
	this->ownDamage = other.ownDamage;
	this->visability = other.visability;
	this->level = other.level;
	this->landDamage = other.landDamage;
	this->landDefence = other.landDefence;

	this->weapon = std::shared_ptr<Weapon>(new Weapon(*other.weapon));
	this->armor = std::shared_ptr<Armor>(new Armor(*other.armor));
	this->moveBehavior = std::shared_ptr<MoveBehavior>(new MoveBehavior(*other.moveBehavior));
	this->attackBehavior = std::shared_ptr<AttackBehavior>(new AttackBehavior(*other.attackBehavior));

	this->observerSize = 0;
	this->observerCount = 0;
	this->coordX = other.coordX;
	this->coordY = other.coordY;
	return *this;
}

HumanWithGun & HumanWithGun::operator=(HumanWithGun && other)
{
	if (&other == this) {
		return *this;
	}

	this->hp = other.hp;
	this->maxHP = other.maxHP;
	this->ownArmor = other.ownArmor;
	this->ownDamage = other.ownDamage;
	this->visability = other.visability;
	this->level = other.level;
	this->landDamage = other.landDamage;
	this->landDefence = other.landDefence;

	this->weapon = std::shared_ptr<Weapon>(new Weapon(*other.weapon));
	this->armor = std::shared_ptr<Armor>(new Armor(*other.armor));
	this->moveBehavior = std::shared_ptr<MoveBehavior>(new MoveBehavior(*other.moveBehavior));
	this->attackBehavior = std::shared_ptr<AttackBehavior>(new AttackBehavior(*other.attackBehavior));

	this->observerSize = 0;
	this->observerCount = 0;
	this->coordX = other.coordX;
	this->coordY = other.coordY;

	return *this;
}


HumanWithGun::~HumanWithGun()
{
}

char HumanWithGun::getChar()
{
	return 'W';
}

std::string HumanWithGun::getPath() {
    return "humanWithGun.png";
}
