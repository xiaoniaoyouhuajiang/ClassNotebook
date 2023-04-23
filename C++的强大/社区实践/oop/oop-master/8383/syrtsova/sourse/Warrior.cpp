#include "pch.h"
#include "Warrior.h"
#include "Classes.h"


void Swordsman::selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine)
{
	switch (ch)
	{
	case 1:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			shield_strike(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Мечник зря потратил силы!";
			force -= 1;
		}
	} break;
	case 2:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			swepping_blow(this->getLink(link), field,adapter);
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Мечник зря потратил силы!";
			force -= 1;
		}
	} break;
	case 3: skill_berserk(field,adapter);
		break;
	case 4: 
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			furious_strike(this->getLink(link), field,adapter);
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Мечник зря потратил силы!";
			force -= 1;
		}
	} break;
	}
	if (force <= 0)
	{
		cout << endl << "Силы иссякли";
		force = 0;
	}	
}

void Swordsman::showSkills(Adapter *adapter) {
	cout << endl << "Количество силы: "       << force    << "Упорство: "           << _zeal
		 << endl << "1: <Удар щитом>"         << "\t\t"   << "Затраты силы: "       << _forcecost[0]
		 << endl << "2: <Стремительный удар>" << "\t\t"   << "Затраты силы: "       << _forcecost[1]
		 << endl << "3: <Берсерк>"            << "\t\t\t" << "Затраты силы: "       << _forcecost[3]
		 << endl << "4: <Яростный удар>"      << "\t\t"   << "Требуется упорства: " << _forcecost[2];
	adapter->request("Мечник докладывает о доступных способностях");
}

Swordsman::Swordsman(int &x, int &y) : Classe_warrior('F', 50, 8, 10)
{
	XY.x = x;
	XY.y = y;
	_zeal = 10;
	spr.setAtrib(_zeal);
	for (int i = 0; i < 4; i++)
	{
		nameSkills[i] = nameSkill[i];
	}
}
void Swordsman::furious_strike(Units* unit, Map* field, Adapter *adapter)
{
	if (_zeal >= _forcecost[2])
	{
		cout << endl << "Мечник совершает яростный удар! Противник теряет много крови.";
		adapter->request("Мечник совершает яростный удар");
		unit->health.change(-8);
		unit->reaction(field, adapter);
		force -= 3;
		_zeal -= _forcecost[2];
	}
	else
	{
		cout << endl << "Недостаточно упороства!";
		adapter->request("Мечник отменяет способность, недостаточно упорства");
	}
}
void Swordsman::shield_strike(Units* unit, Map* field, Adapter *adapter)
{
	if (force >= _forcecost[0])
	{
		cout << endl << "Мечник совершает удар щитом!";
		adapter->request("Мечник совершает удар щитом");
		unit->health.change(-3);
		unit->reaction(field, adapter);
		force -= _forcecost[0];
		_zeal += 1;
	}
	else
	{
		cout << endl << "Недостаточно силы!";
		adapter->request("Мечник отменяет способность, недостаточно силы");
	}
}

void Swordsman::swepping_blow(Units* unit, Map* field, Adapter *adapter)
{
	if (force >= _forcecost[1])
	{
		cout << endl << "Мечник наносит стремительный удар! Противник не успевает увернуться и получает урон.";
		adapter->request("Мечник наносит стремительный удар");
		unit->health.change(-5);
		unit->reaction(field, adapter);
		force -= _forcecost[1];
		_zeal += 2;
	}
	else
	{
		cout << endl << "Недостаточно силы!";
		adapter->request("Мечник отменяет способность, недостаточно силы");
	}
}

Swordsman::~Swordsman()
{
	cout << endl << "Мечник был уничтожен!";
}


Spear::Spear(int &x, int &y) : Classe_warrior('G', 40, 10, 8)
{
	XY.x = x;
	XY.y = y;
	_rage = 10;
	spr.setAtrib(_rage);
	for (int i = 0; i < 4; i++)
	{
		nameSkills[i] = nameSkill[i];
	}
}



void Spear::selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine)
{
	switch (ch)
	{
	case 1:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			exact_blow(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Рыцарь зря потратил силы!";
			force -= 1;
		}
	} break;
	case 2:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			roll_forward(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Рыцарь зря потратил силы!";
			force -= 1;
		}
	} break;
	case 3: skill_berserk(field, adapter);
		break;
	case 4:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			spear_strike(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Рыцарь зря потратил силы!";
			force -= 1;
		}
	} break;
	}
	if (force <= 0)
	{
		cout << endl << "Силы иссякли";
		force = 0;
	}
}
void Spear::showSkills(Adapter *adapter) {
	cout << endl << "Количество силы: "   << force    << "Ярость: "            << _rage
		 << endl << "1: <Удар копьём>"    << "\t\t"   << "Затраты силы: "      << _forcecost[0]//1
		 << endl << "2: <Накат>"          << "\t\t\t" << "Затраты силы: "      << _forcecost[1]//4
		 << endl << "3: <Берсерк>"        << "\t\t\t" << "Затраты силы: "      << _forcecost[2]//10
		 << endl << "4: <Точный удар>"    << "\t\t"   << "Необходимо ярости: " << _forcecost[3];//5
	adapter->request("Рыцарь докладывает о доступных способностях");
}

void Spear::exact_blow(Units* unit, Map *field, Adapter *adapter)
{
	if (force >= _forcecost[0])
	{
		cout << endl << "Рыцарь наносит удар копьём.";
		adapter->request("Рыцарь наносит удар копьём");
		unit->health.change(-3);
		unit->reaction(field, adapter);
		force -= _forcecost[0];
		_rage += 1;
	}
	else
	{
		cout << endl << "Недостаточно силы!";
		adapter->request("Мечник отменяет способность, недостаточно силы");
	}
}
void Spear::roll_forward(Units* unit, Map *field, Adapter *adapter)
{
	if (force >= _forcecost[1])
	{
		cout << endl << "Рыцарь делает накат копьем.";
		adapter->request("Рыцарь делает накат копьем");
		unit->health.change(-2);
		unit->reaction(field, adapter);
		force -= _forcecost[1];
		_rage += 2;
	}
	else
	{
		cout << endl << "Недостаточно силы!";
		adapter->request("Мечник отменяет способность, недостаточно силы");
	}
}
void Spear::spear_strike(Units* unit, Map *field, Adapter *adapter)
{
	if (_rage >= _forcecost[3])
	{
		cout << endl << "Рыцарь наносит точный удар! Противник не успевает увернуться и получает урон.";
		adapter->request("Рыцарь наносит точный удар");
		unit->health.change(-5);
		unit->reaction(field,adapter);
		_rage -= _forcecost[3];
		force -= 3;
	}
	else
	{
		cout << endl << "Недостаточно ярости!";
		adapter->request("Мечник отменяет способность, недостаточно ярости");
	}
}
Spear::~Spear()
{
	cout << endl << "Рыцарь был уничтожен!";
}


