#include "UnitBase.h"

void Hp::decrease(int n)
{
	hp -= n;
}

void Hp::increase(int n)
{
	hp += n;
}

int Hp::get()
{
	return hp;
}

void Damage::decrease(int n)
{
	damage -= n;
}

void Damage::increase(int n)
{
	damage += n;
}

int Damage::get()
{
	return damage;
}

void UnitBase::increaseDamage(size_t n)
{
	damage.increase(n);
}

void UnitBase::setPoint(Point p)
{
	this->p = p;
}

void UnitBase::tellAboutMe()
{
	std::cout << "Info about unit:\n";
	std::cout << "Unit hp - " << hp.get() << "\n";
	std::cout << "Unit damage - " << damage.get() << "\n";
	std::cout << "Unit range - " << range << "\n";
	std::cout << "Unit coordinates - " << p.x << " " << p.y << "\n";
}

void UnitBase::operator()(std::shared_ptr<NtrlObj> ntrl)
{
	auto data = ntrl->who();
	if (std::find(data.begin(), data.end(), name) == data.end())
		return;

	NtrlObjEffect effect = ntrl->get();
	switch (effect.what)
	{
	case EffectTypes::damage:
		damage.increase(effect.how_much);
		break;
	case EffectTypes::hp:
		hp.increase(effect.how_much);
		break;
	case EffectTypes::range:
		range += effect.how_much;
		break;
	default:
		break;
	}
}

void UnitBase::operator()(LandscapeInfo effect)
{
	switch (effect.what)
	{
	case EffectTypes::damage:
		damage.increase(effect.how_much);
		break;
	case EffectTypes::range:
		range += effect.how_much;
		break;
	case EffectTypes::hp:
		hp.increase(effect.how_much);
		break;
	}
}

void UnitBase::update()
{
	damage.increase(20);
}
