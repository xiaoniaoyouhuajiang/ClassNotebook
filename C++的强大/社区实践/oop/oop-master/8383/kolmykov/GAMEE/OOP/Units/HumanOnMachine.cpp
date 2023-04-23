#include "HumanOnMachine.h"



HumanOnMachine::HumanOnMachine()
{
	armor = std::shared_ptr<Armor> (new HeavyArmor());
	hp = 200;
	maxHP = 200;
}

HumanOnMachine::HumanOnMachine(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep)
:Human(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep){
	armor = std::shared_ptr<Armor>(new HeavyArmor());
}

HumanOnMachine::HumanOnMachine(int x, int y, int level):Human(x, y, level)
{
	armor = std::shared_ptr<Armor> (new HeavyArmor());
	hp = 200;
	maxHP = 200;
}

HumanOnMachine::HumanOnMachine(const HumanOnMachine & other):Human(other)
{
}

HumanOnMachine::HumanOnMachine(HumanOnMachine && other):Human(other)
{
}

HumanOnMachine& HumanOnMachine::operator=(const HumanOnMachine & other)
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

HumanOnMachine & HumanOnMachine::operator=(HumanOnMachine && other)
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


HumanOnMachine::~HumanOnMachine()
{
}

char HumanOnMachine::getChar()
{
	return 'U';
}
