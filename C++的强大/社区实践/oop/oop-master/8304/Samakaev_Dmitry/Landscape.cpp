#include "Landscape.h"

LandscapeProxy::LandscapeProxy(LandscapeType type)
{
	switch (type)
	{
	case LandscapeType::desert:
		cur = new DesertLandscape;
		break;
	case LandscapeType::mountain:
		cur = new MountainLandscape;
		break;
	case LandscapeType::swamp:
		cur = new SwampLandscape;
		break;
	default:
		break;
	}
}

void LandscapeProxy::setEffect(Unit* unit)
{
	cur->setEffect(unit);
}

void DesertLandscape::setEffect(Unit* unit)
{
	auto unitType = unit->type;
	LandscapeEffect effect = { LandscapeEffectType::hp, 0 };

	switch (unitType)
	{
	case unitType::Catapult:
		effect = { LandscapeEffectType::damage, 20 };
		break;
	case unitType::Siege_tower:
		effect = { LandscapeEffectType::damage, 10 };
		break;
	case unitType::Archer:
		effect = { LandscapeEffectType::damage, -5 };
		break;
	default:
		break;
	}

	unit->landEffect = effect;
}

void MountainLandscape::setEffect(Unit* unit)
{
	auto unitType = unit->type;
	LandscapeEffect effect = { LandscapeEffectType::hp, 0 };

	switch (unitType)
	{
	case unitType::Catapult:
		effect = { LandscapeEffectType::damage, 20 };
		break;
	case unitType::Archer:
		effect = { LandscapeEffectType::damage, 30 };
		break;
	case unitType::Knight:
		effect = { LandscapeEffectType::armor, -5 };
		break;
	default:
		break;
	}

	unit->landEffect = effect;
}

void SwampLandscape::setEffect(Unit* unit)
{
	auto unitType = unit->type;
	LandscapeEffect effect = { LandscapeEffectType::hp, 0 };

	switch (unitType)
	{
	case unitType::Catapult:
		effect = { LandscapeEffectType::damage, -5 };
		break;
	case unitType::Mage:
		effect = { LandscapeEffectType::damage, 15 };
		break;
	case unitType::Rogue:
		effect = { LandscapeEffectType::armor, 10 };
		break;
	default:
		break;
	}

	unit->landEffect = effect;
}
