#include "pch.h"
#include "Warlock.h"
#include "Classes.h"
#include "Bases.h"
#include "Units.h"
#include "Map.h"
#include <windows.h>
#include <conio.h>


Magician::Magician(int &x, int &y) : Classe_warlock('M', 50, 6, 4, 100)
{
	XY.x = x;
	XY.y = y;
	_ether = 200;
	for (int i = 0; i < 4; i++)
	{
		nameSkills[i] = nameSkill[i];
	}
}

void Magician::selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine)
{
	switch (ch)
	{
	case 1: 
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			meteorite(this->getLink(link), field, adapter);
			return;
		}
		else
		{
		cout << endl << "На выбранной клетке нет юнитов!" << endl << "Маг отменяет заклинание, но часть маны истрачена!";
		mana -= 1;
		Sleep(10);
		}
	}
		break;
	case 2: 
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{

			storm(this->getLink(link),field,adapter);
			return;
		}
		else 
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Маг отменяет заклинание, но часть маны истрачена!";
			mana -= 1;
			Sleep(10);
		}
	}
		break;
	case 3: 
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			skill_fireball(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Маг отменяет заклинание, но часть маны истрачена!";
			mana -= 1;
			Sleep(10);
		}
	}
		break;
	case 4: {
		ARMAGEDON(field, link,adapter);
		return; 
}
		break;
	}
	if (mana <= 0)
	{
		cout << endl << "Мана иссякла!";
		Sleep(10);
		mana = 0;
	}
}

void Magician::showSkills(Adapter *adapter)
{
	cout << endl << "Количество маны: " << mana     << "\t\t"              << "Количество эфира: " << this->_ether;
	cout << endl << "1: <Метеорит> "    << "\t\t\t" << "Затрата маны: "    << _manacost[2] 
		 << endl << "2: <Шторм>"        << "\t\t\t" << "Затрата маны: "    << _manacost[1]
		 << endl << "3: <Огненный шар>" << "\t\t"   << "Затарта маны: "    << _manacost[0]
		 << endl << "4: <АРМАГЕДДОН>"   << "\t\t\t" << "Нужно эфира: "	   << _manacost[3];
	adapter->request("Маг докладывает о доступных способностях");
}

void Magician::ARMAGEDON(Map* field, Units **link, Adapter *adapter)
{
	if (_ether >= _manacost[3]) {
		cout << endl << "Мага переполняет тёмная энергия! Он не в состоянии её контролировать."
			<< endl << "Из под земли вырывается лава, а с небес падают метеориты."
			<< endl << "Силы и здровье всех инитов, кто попал в радиус действия стремятся к нулю."
			<< endl << "Настал АРМАГЕДДОН.";
		adapter->request("Маг использует способность <АРМАГЕДДОН>");
		cout << endl << endl << "Нажмите на любую кнопку, чтобы продолжить игру";
		_getch();
		Object* o = new Object('@');
		o->color = colorLand::red;

		// Правая клетка 6
		if ((*field).isUnit(this->XY.x + 1, XY.y))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y;
			Units *un = this->getLink(link);
			this->deleteLink(un, link);
		}
		Sleep(10);
		(*field).addOnMap(this->XY.x + 1, this->XY.y, o);
		system("cls");
		(*field).printMap();
		// Правая верхняя клетка 3
		if ((*field).isUnit(this->XY.x + 1, XY.y - 1))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(link);
			this->deleteLink(un, link);
		}
		Sleep(10);
		(*field).addOnMap(this->XY.x + 1, this->XY.y - 1, o);
		system("cls");
		(*field).printMap();
		// Левая клетка 4 
		if ((*field).isUnit(this->XY.x - 1, XY.y))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y;
			Units *un = this->getLink(link);
			this->deleteLink(un, link);
		}
		Sleep(100);
		(*field).addOnMap(this->XY.x - 1, this->XY.y, o);
		system("cls");
		(*field).printMap();
		// Правая нижняя клетка 9
		if ((*field).isUnit(this->XY.x + 1, XY.y + 1))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(link);
			this->deleteLink(un, link);
		}
		Sleep(10);
		(*field).addOnMap(this->XY.x + 1, this->XY.y + 1, o);
		system("cls");
		(*field).printMap();
		// Нижняя клетка 8
		if ((*field).isUnit(this->XY.x, XY.y + 1))
		{
			_xy.x = this->XY.x;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(link);
			this->deleteLink(un, link);
		}
		Sleep(10);
		(*field).addOnMap(this->XY.x, this->XY.y + 1, o);
		system("cls");
		(*field).printMap();
		// Верхняя левая клетка 1
		if ((*field).isUnit(this->XY.x - 1, XY.y - 1))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(link);
			this->deleteLink(un, link);
		}
		Sleep(10);
		(*field).addOnMap(this->XY.x - 1, this->XY.y - 1, o);
		system("cls");
		(*field).printMap();
		// Нижняя левая клекта 7
		(*field).addOnMap(this->XY.x - 1, this->XY.y + 1, o);
		system("cls");
		(*field).printMap();
		if ((*field).isUnit(this->XY.x - 1, XY.y + 1))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(link);
			this->deleteLink(un, link);
		}
		Sleep(10);
		
		//Верхняя клетка 2
		if ((*field).isUnit(this->XY.x, XY.y - 1))
		{
			_xy.x = this->XY.x;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(link);
			this->deleteLink(un, link);
		}
		Sleep(10);
		(*field).addOnMap(this->XY.x, this->XY.y - 1, o);
		system("cls");
		(*field).printMap();

		// Центральная клетка 5
		(*field).addOnMap(this->XY.x, this->XY.y, o);
		system("cls");
		(*field).printMap();
		Sleep(10);
		_xy.x = this->XY.x;
		_xy.y = this->XY.y;
		Units *un = this->getLink(link);
		this->deleteLink(un, link);
		return;
	}
	else
	{
		cout << endl << "Недостаточно темной энергии!";
		adapter->request("Маг отменяет способность, недостаточно тёмной энергии");
	}
}

void Magician::meteorite(Units* unit, Map* field, Adapter *adapter)
{
	if (mana >= _manacost[1])
	{
		cout << endl << "С неба летит огромный метеорит!";
		adapter->request("Маг использует способность <Метеорит>");
		unit->health.change(-5);
		unit->reaction(field, adapter);
		mana -= _manacost[1];
		_ether += 5;
	}
	else
	{
		cout << endl << "Недостаточно маны!";
		adapter->request("Маг отменяет способность, недостаточно маны");
	}
}

void Magician::storm(Units* unit, Map* field, Adapter *adapter)
{
	if (mana >= _manacost[2])
	{
		cout << endl << "Тучи сгущаюстя. Молнии и ураган наносят огромный урон, не щадя никого";
		cout << endl << endl << "Нажмите на любую кнопку, чтобы продолжить игру";
		adapter->request("Маг использует способность <Шторм>");
		_getch();
		unit->health.change(-10);
		this->health.change(-4);
		unit->reaction(field, adapter);
		this->reaction(field, adapter);
		mana -= _manacost[2];
		_ether += 10;
	}
	else
	{
		cout << endl << "Недостаточно маны!";
		adapter->request("Маг отменяет способность, недостаточно маны");
	}
}

Magician::~Magician()
{
	cout << endl << "Маг был уничтожен!";
}


void Healer::selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine)
{
	if (mana <= 0)
	{
		cout << endl << "Мана иссякла!";
		mana = 0;
		return;
	}
	switch (ch)
	{
	case 1:
	{
		cover(adapter);
	} break;
	case 2:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			heal(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Целитель просто начинает молиться.";
			cover(adapter);
		}
	} break;
	case 3:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			skill_fireball(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "На выбранной клетке нет юнитов!" << endl << "Целитель отменяет заклинание, но часть маны истрачена!";
			mana -= 1;
		}
	} break;
	case 4: mass_heal(field, link, adapter);
		break;
	}

}

Healer::Healer(int &x, int &y) : Classe_warlock('H', 40, 8, 2, 80)
{
	XY.x = x;
	XY.y = y;
	_prayer = 10;
	for (int i = 0; i < 4; i++)
	{
		nameSkills[i] = nameSkill[i];
	}
}

void Healer::showSkills(Adapter *adapter)
{
	cout << endl << "Количество маны: " << mana << "\t\t"   << "Сила молитвы: "		    << _prayer;
	cout << endl << "1: <Молитва> "             << "\t\t\t" << "Затрата маны: "         << _manacost[2]
		 << endl << "2: <Исцеление>"            << "\t\t\t" << "Затрата маны: "         << _manacost[1]
		 << endl << "3: <Огненный шар>"         << "\t\t"   << "Затрата маны: "         << _manacost[0]
		 << endl << "4: <Массовое исцеление>"   << "\t\t"   << "Нужно священных слов: " << _manacost[3];
	adapter->request("Целитель докладывает о доступных способностях");
}


void Healer::heal(Units* unit, Map* field, Adapter *adapter)
{
	if (mana >= _manacost[1])
	{
		cout << endl << "Целитель достаёт манускрипт и колбы с зельями и приступает к исцелению";
		cout << endl << endl << "Нажмите на любую кнопку, чтобы продолжить игру";
		_getch();
		adapter->request("Маг использует способность <Исцеление>");
		unit->health.change(2);
		unit->reaction(field, adapter, true);
		mana -= _manacost[1];
	}
	else
	{
		cout << endl << "Недостаточно маны!"; 
		adapter->request("Целитель отменяет способность, недостаточно маны");
		Sleep(10);
	}
}
void Healer::mass_heal( Map* field, Units **link, Adapter *adapter)
{
	if (_prayer >= _manacost[3])
	{
		cout << endl << "Целитель взывает к небесам, юниты в радиусе 1 клетки исцелены";
		cout << endl << endl << "Нажмите на любую кнопку, чтобы продолжить игру";
		adapter->request("Маг использует способность <Массовое исценеление>");
		_getch();
		// Правая клетка 6
		if ((*field).isUnit(this->XY.x + 1, XY.y))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y;
			Units *un = this->getLink(link);
			un->health.change(3);
			un->reaction(field, adapter, true);
		}
		// Правая верхняя клетка 3
		if ((*field).isUnit(this->XY.x + 1, XY.y - 1))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(link);
			un->health.change(3);
			un->reaction(field, adapter, true);
		}
		// Левая клетка 4 
		if ((*field).isUnit(this->XY.x - 1, XY.y))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y;
			Units *un = this->getLink(link);
			un->health.change(3);
			un->reaction(field, adapter, true);
		}
		// Правая нижняя клетка 9
		if ((*field).isUnit(this->XY.x + 1, XY.y + 1))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(link);
			un->health.change(3);
			un->reaction(field, adapter, true);
		}
		// Нижняя клетка 8
		if ((*field).isUnit(this->XY.x, XY.y + 1))
		{
			_xy.x = this->XY.x;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(link);
			un->health.change(3);
			un->reaction(field, adapter, true);
		}
		// Верхняя левая клетка 1
		if ((*field).isUnit(this->XY.x - 1, XY.y - 1))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(link);
			un->health.change(3);
			un->reaction(field, adapter, true);
		}
		// Нижняя левая клекта 7
		if ((*field).isUnit(this->XY.x - 1, XY.y + 1))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(link);
			un->health.change(3);
			un->reaction(field, adapter, true);
		}
		//Верхняя клетка 2
		if ((*field).isUnit(this->XY.x, XY.y - 1))
		{
			_xy.x = this->XY.x;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(link);
			un->health.change(3);
			un->reaction(field, adapter, true);
		}
		// Центральная клетка 5
		this->health.change(3);
	}	
	else
	{
		cout << endl << "Священной энергии не хватает!";
		adapter->request("Целитель отменяет способность, недостаточно священной энергии");
		Sleep(10);
	}
}


void Healer::cover(Adapter *adapter)
{
	if (mana >= _manacost[2])
	{
		cout << endl << "Целитель читает молитву, количество священных слов увеличивается";
		cout << endl << endl << "Нажмите на любую кнопку, чтобы продолжить игру";
		adapter->request("Целитель читает молитву");
		_getch();
		_prayer += 1;
	}
	else
	{
		cout << endl << "Недостаточно маны!";
		adapter->request("Целитель отменяет способность, недостаточно маны");
		Sleep(10);
	}
}


Healer::~Healer()
{
	cout << endl << "Цилитель был уничтожен!";
	Sleep(10);
}


