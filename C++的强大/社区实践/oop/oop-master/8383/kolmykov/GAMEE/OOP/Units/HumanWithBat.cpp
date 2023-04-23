#include "HumanWithBat.h"



HumanWithBat::HumanWithBat()
{
	attackBehavior = std::shared_ptr<AttackBehavior>(new AttackWithBat());
	weapon = std::shared_ptr<Weapon>(new Bat());
	type = UnitType::HUMAN_WITH_BAT;
}

HumanWithBat::HumanWithBat(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep)
:MeleeHuman(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep){
	attackBehavior = std::shared_ptr<AttackBehavior>(new AttackWithBat());
	weapon = std::shared_ptr<Weapon>(new Bat());
	type = UnitType::HUMAN_WITH_BAT;
}

HumanWithBat::HumanWithBat(int x, int y, int level):MeleeHuman(x, y, level)
{
	attackBehavior = std::shared_ptr<AttackBehavior> (new AttackWithBat());
	weapon = std::shared_ptr<Weapon>(new Bat());
	type = UnitType::HUMAN_WITH_BAT;
}

HumanWithBat::HumanWithBat(const HumanWithBat & other):MeleeHuman(other)
{
}

HumanWithBat::HumanWithBat(HumanWithBat && other):MeleeHuman(other)
{
}

HumanWithBat& HumanWithBat::operator=(const HumanWithBat & other)
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

HumanWithBat & HumanWithBat::operator=(HumanWithBat && other)
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


HumanWithBat::~HumanWithBat()
{

}

char HumanWithBat::getChar()
{
	return 'B';
}


std::string HumanWithBat::getPath() {
    return "humanWithBat.png";
}
