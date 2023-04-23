#pragma once
#include "Rule.h" 
#include "Resourses.h"


template <typename T, size_t n>
struct Game;


template <typename T>
struct Game<T, 2>
{
	Game(std::vector<std::shared_ptr<UnitBase>>& f_units, 
		 std::vector<std::shared_ptr<UnitBase>>& s_units)
	{
		rule.setUnits(f_units, s_units);
	}

	size_t getPlayerNumber()
	{
		return rule.getPlayerNumber();
	}

	std::vector<std::shared_ptr<UnitBase>>& getCurPlayerUnits()
	{
		return rule.getCurPlayerUnits();
	}

	void changePlayer()
	{
		rule.changePlayer();
	}

	PtsPair getCurPlayerPts()
	{
		return rule.getCurPlayerPts();
	}

	

private:
	T rule;
	RuleTypes type = RuleTypes::fastGame;
};


template <typename T>
struct Game<T, 3>
{
	Game(std::vector<std::shared_ptr<UnitBase>>& f_units, 
		 std::vector<std::shared_ptr<UnitBase>>& s_units, 
		 std::vector<std::shared_ptr<UnitBase>>& t_units)
	{
		rule.setUnits(f_units, s_units, t_units);
	}

	size_t getPlayerNumber()
	{
		return rule.getPlayerNumber();
	}

	std::vector<std::shared_ptr<UnitBase>>& getCurPlayerUnits()
	{
		return rule.getCurPlayerUnits();
	}

	void changePlayer()
	{
		rule.changePlayer();
	}

	size_t getCurPlayerPts()
	{
		return rule.getCurPlayerPts();
	}

private:
	T rule;
	RuleTypes type = RuleTypes::standartGame;
};
