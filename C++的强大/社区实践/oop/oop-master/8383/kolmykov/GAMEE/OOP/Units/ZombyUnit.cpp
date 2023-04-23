#include "ZombyUnit.h"



ZombyUnit::ZombyUnit(int hp, int maxHP, int ownArmor, int ownDamage, bool visability, int level, int landDamage, int landDefence, std::shared_ptr<std::shared_ptr<ObserverInterface>[]> observers, int observerSize, int observerCount, int coordX, int coordY, std::shared_ptr<Mediator> mediator, size_t lastStep)
:Unit(hp, maxHP, ownArmor, ownDamage, visability, level, landDamage, landDefence, observers, observerSize, observerCount, coordX, coordY, mediator, lastStep){
	kind = Kind::ZOMBY;
}

ZombyUnit::ZombyUnit() {
	kind = Kind::ZOMBY;
}

ZombyUnit::ZombyUnit(int x, int y, int level):Unit(x, y, level) {
	kind = Kind::ZOMBY;
}

ZombyUnit::ZombyUnit(const ZombyUnit & other):Unit(other)
{
	kind = Kind::ZOMBY;
}

ZombyUnit::ZombyUnit(ZombyUnit && other):Unit(other)
{
	kind = Kind::ZOMBY;
}

ZombyUnit& ZombyUnit::operator=(const ZombyUnit & other)
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
	this->kind = other.kind;

	return *this;
}

ZombyUnit & ZombyUnit::operator=(ZombyUnit && other)
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
	this->kind = other.kind;

	return *this;
}

ZombyUnit::~ZombyUnit()
{
}

char ZombyUnit::getChar()
{
	return 'U';
}


