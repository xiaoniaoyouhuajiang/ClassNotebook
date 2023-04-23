#pragma once
#include "UnitBase.h"
#include "Resourses.h"
#include <map>

struct LandscapeInterface
{
	virtual std::vector<char> who() = 0;
	virtual LandscapeInfo how(char c) = 0;
};

struct Ground : LandscapeInterface
{
	std::vector<char> who();
	LandscapeInfo how(char c);
};

struct Mountain : LandscapeInterface
{
	std::vector<char> who();
	LandscapeInfo how(char c);
};

struct Swamp : LandscapeInterface
{
	std::vector<char> who();
	LandscapeInfo how(char c);
};

struct LandscapeProxy
{
	LandscapeInfo get(LandscapeTypes type, char c);
private:
	std::map<std::pair<LandscapeTypes, char>, LandscapeInfo> d;
};
