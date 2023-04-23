#pragma once
#include "Object.h"
#include <limits>
#include <iostream>
#include "Map.h"
#include "Attribute.h"
#include "Neutral.h"
#include "Adapter.h"


/// Класс Юнита
class Units : public Object
{
public:
	bool dragonblade;
	Name name;
	Health health;
	Armor armor;
	Attack attack;
	Radius radius;
	SpecialResources spr;
	string message;
	string nameSkills[4];
	struct State {
		bool is_active = false;
		bool is_skills = false;
		bool is_movie = false;
		bool is_direction = false;
		int skill = NULL;
		bool is_save = false;
		bool is_loading = false;
	}state;
	virtual void showSkills(Adapter *adapter) = 0;
	virtual void selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine = false) = 0;
	struct Coordinates {
		int x, y;
	}XY;
	struct Line {
		int x, y;
	}_xy;
	void action(int &act, Creating *neutral);
	Units* getLink(Units **link);
	void managment(Map *field, Units **link, Creating *neutral, Adapter *adapter);
	void selectLine(Adapter *adapter);
	void useSkill(Map *field, Units **link, Adapter *adapter);
	Units(char N,const int &h,const int &ar,const int &at,const int &r);
	void movie(Map *field, Creating *neutral, Adapter *adapter);
	void selected(Map *field, Adapter *adapter);
	void printStats(Adapter *adapter);
	bool rules(Map *field, int x, int y);
	void reaction(Map *field, Adapter *adapter, bool effect = false);
	void deleteLink(Units *un, Units **link);
	virtual ~Units();
protected:
	void operator + (Units* unit);
};

