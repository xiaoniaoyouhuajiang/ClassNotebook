#pragma once
#include "Classes.h"

/// Класс Мага
class Magician : public Classe_warlock
{
private: 
	int _ether;
	int _manacost[4] = { 5, 25, 45, 110 };
public:
	string nameSkill[4] = { "Метеорит", "Шторм", "Огненный шар", "АРМАГЕДДОН"};
	void selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine = false) override;
	void showSkills(Adapter *adapter) override;
	void meteorite(Units* unit, Map* field, Adapter *adapter);
	void ARMAGEDON(Map* field, Units **link, Adapter *adapter);
	void storm(Units* unit, Map* field, Adapter *adapter);
	Magician(int &x, int &y);
	~Magician();
};

/// Класс Целителя
class Healer : public Classe_warlock
{
	int _prayer;
	int _manacost[4] = { 5,10,25,6 };
public:
	string nameSkill[4] = { "Молитва", "Исцеление", "Огненный шар", "Массовое исцеление" };
	void selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine = false) override;
	void showSkills(Adapter *adapter) override;
	void heal(Units* unit, Map* field, Adapter *adapter);
	void mass_heal(Map* field, Units **link, Adapter *adapter);
	void cover(Adapter *adapter);
	Healer(int &x, int &y);
	~Healer();
};




