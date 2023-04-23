#include "HumanOnCar.h"



HumanOnCar::HumanOnCar()
{
	attackBehavior = std::shared_ptr<AttackBehavior>(new CarAttack());
	moveBehavior = std::shared_ptr<MoveBehavior>(new CarMove());
	weapon = std::shared_ptr<Weapon>(new Bat());
	type = UnitType::HUMAN_ON_CAR;
}

HumanOnCar::HumanOnCar(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep)
:HumanOnMachine(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep){
	attackBehavior = std::shared_ptr<AttackBehavior>(new CarAttack());
	moveBehavior = std::shared_ptr<MoveBehavior>(new CarMove());
	weapon = std::shared_ptr<Weapon>(new Bat());
	type = UnitType::HUMAN_ON_CAR;
}

HumanOnCar::HumanOnCar(int x, int y, int level):HumanOnMachine(x, y, level)
{
	attackBehavior = std::shared_ptr<AttackBehavior> (new CarAttack());
	moveBehavior = std::shared_ptr<MoveBehavior>(new CarMove());
	weapon = std::shared_ptr<Weapon>(new Bat());
	type = UnitType::HUMAN_ON_CAR;
}

HumanOnCar::HumanOnCar(const HumanOnCar & other):HumanOnMachine(other)
{
}

HumanOnCar::HumanOnCar(HumanOnCar && other):HumanOnMachine(other)
{
}

HumanOnCar& HumanOnCar::operator=(const HumanOnCar & other)
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

HumanOnCar & HumanOnCar::operator=(HumanOnCar && other)
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


HumanOnCar::~HumanOnCar()
{
}

char HumanOnCar::getChar()
{
	return 'C';
}


std::string HumanOnCar::getPath() {
    return "humanOnCar.png";
}
