#include "HumanWithGrenade.h"



HumanWithGrenade::HumanWithGrenade()
{
	attackBehavior = std::shared_ptr<AttackBehavior>(new GrenadeAttack());
	weapon = std::shared_ptr<Weapon>(new Grenade());
	type = UnitType::HUMAN_WITH_GRENADE;
}

HumanWithGrenade::HumanWithGrenade(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep)
:RangeHuman(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep){
	attackBehavior = std::shared_ptr<AttackBehavior>(new GrenadeAttack());
	weapon = std::shared_ptr<Weapon>(new Grenade());
	type = UnitType::HUMAN_WITH_GRENADE;
}

HumanWithGrenade::HumanWithGrenade(const HumanWithGrenade & other):RangeHuman(other)
{
}

HumanWithGrenade::HumanWithGrenade(int x, int y, int level):RangeHuman(x, y, level)
{
	attackBehavior = std::shared_ptr<AttackBehavior>(new GrenadeAttack());
	weapon = std::shared_ptr<Weapon>(new Grenade());
	type = UnitType::HUMAN_WITH_GRENADE;
}

HumanWithGrenade::HumanWithGrenade(HumanWithGrenade && other):RangeHuman(other)
{
}

HumanWithGrenade& HumanWithGrenade::operator=(const HumanWithGrenade & other)
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

HumanWithGrenade & HumanWithGrenade::operator=(HumanWithGrenade && other)
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


HumanWithGrenade::~HumanWithGrenade()
{
}

char HumanWithGrenade::getChar()
{
	return 'G';
}


std::string HumanWithGrenade::getPath() {
    return "humanWithGrenade.png";
}
