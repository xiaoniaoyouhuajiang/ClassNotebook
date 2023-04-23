#pragma once

enum class LandscapeType
{
	desert,
	mountain,
	swamp
};

enum class LandscapeEffectType
{
	armor,
	damage,
	hp
};

struct LandscapeEffect
{
	LandscapeEffectType type;
	int how_much;
};