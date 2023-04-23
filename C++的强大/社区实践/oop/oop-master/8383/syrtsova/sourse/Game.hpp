#pragma once
#include "Recorder.h"
#include "Adapter.h"
#include "Proxy.h"
#include "Landscape.h"
#include "Neutral.h"
#include "Map.h"
#include "Bases.h"
#include <memory>
#include <string>
#include <iomanip>
#include "Facade.h"
#include <iostream>
#include <Windows.h>
#include "Rules.h"
#include "Rule_2.h"
#include "Rule_1.h"
#include "Error.h"

class Originator;
class Caretaker;

template <typename T>
/// Шаблонный класс Игры
class Game
{
	static Game* game;
	int _x_max, _y_max;
	std::shared_ptr<T> rule = nullptr;
	Game(std::shared_ptr<T> rule, int x = 0, int y = 0);
	bool log = false;
public:
	Game(Game&) = delete;
	static Game<T>* get_game(std::shared_ptr<T> rule, int x = 0, int y = 0);
	int _countermoves_1;
	int _countermoves_2;
	bool _multiplayer;
	bool logToFile = true, logToTerminal = false, withoutLog = false;
	bool isUnitSelected = false;
	void changer();
	bool typeRules();
	T* getRule();
	Map* field;
	Recorder *rec;
	Proxy *proxy;
	Adapter *adapter;
	Landscape *land;
	Creating *neutral;
	Bases *base;
	Bases *base_2 = NULL;
	void choice_map(Adapter *adapter);
	int management(Adapter *adapter);
	void control(Bases* base, int &countermoves);
	int xMax();
	int yMax();
};


#include "Originator.h"
#include "Caretaker.h"



template <typename T>
Game<T>* Game<T>::game = nullptr;

template <typename T>
Game<T>::Game(std::shared_ptr<T> rule, int x, int y) : rule(rule)
{
	rec = new Recorder;
	proxy = new Proxy(rec, logToFile, logToTerminal, withoutLog);
	adapter = new Adapter(proxy);
	
	if (rule->player_count == 1)
	{
		_countermoves_1 = rule->countermoves;
		_countermoves_2 = 0;
	}
	else
	{
		_countermoves_1 = rule->countermoves / 2;
		_countermoves_2 = rule->countermoves / 2;
	}
	
	

	if (x == 0 && y == 0)
	{
		choice_map(adapter);
	}
	else
	{
		log = true;
		_x_max = x;
		_y_max = y;
	}
	field = new Map(_x_max, _y_max);
	if (!log)
	{
		land = new Landscape(_x_max, _y_max, field);
		neutral = new Creating(_x_max, _y_max, field);
		base = new Bases(1, 1, 'B', 10, 100, rule->start_resourses, rule->number_moves, adapter);
		(*field).addOnMap(base->X, base->Y, base);
		if (rule->player_count == 2)
		{
			base_2 = new Bases(_x_max, _y_max, 'B', 12, 1000, rule->start_resourses, rule->number_moves, adapter);
			(*field).addOnMap(base_2->X, base_2->Y, base_2);
			changer();
		}
		else
			control(base, _countermoves_1);
	}
	else
	{
		neutral = new Creating(_x_max, _y_max, field, true);
		base = new Bases(1, 1, 'B', 10, 1000, rule->start_resourses, rule->number_moves, adapter);
	}

}

template<typename T>
Game<T>* Game<T>::get_game(std::shared_ptr<T> rule, int x, int y) {
	if (game == nullptr) {
		game = new Game<T>(rule, x, y);
	}
	return game;
}



template <typename T>
void Game<T>::changer()
{
	while (_countermoves_1 != 0 && _countermoves_2 != 0)
	{
		if (_countermoves_1 != 0)
			control(base, _countermoves_1);
		if (_countermoves_2 != 0)
			control(base_2, _countermoves_2);
	}
}



template <typename T>
void Game<T>::control(Bases* base, int &countermoves)
{
	while (true)
	{
		system("cls");
		(*field).printMap();
		int ch = management(adapter);
		cout << endl;
		switch (ch)
		{
		case 1: {
			base->functional(field, neutral, adapter);
			for (int i = 0; i < base->count_units; i++)
			{
				if (base->getLink(i + 1)->state.is_active)
				{
					isUnitSelected = true;
					if (base->getLink(i + 1)->state.is_save)
					{
						std::string fout = "save";
						Originator *org = new Originator(fout, true);
						Caretaker *ct = new Caretaker(org);
						Units *selectedUnit = base->getLink(i + 1);
						int currNumBase = 1;
						org->save(this, isUnitSelected, logToFile, logToTerminal, withoutLog, selectedUnit, currNumBase);
					}
					else if (base->getLink(i + 1)->state.is_loading)
					{
						std::string fout = "save";
						Originator *org = new Originator(fout, false);
						Caretaker *ct = new Caretaker(org);
						Units *selectedUnit = base->getLink(i);
						int currNumBase = 1;
						org->restore(this, isUnitSelected, logToFile, logToTerminal, withoutLog, currNumBase);
					}
				}
			}
		}
				break;
		case 2: {
			int un;
			if (base->showAllUnits(adapter))
			{
				cout << endl << "Выберите юнита по его ID: ";
				cin >> un;
				string message = "Пользователь выбрал " + base->getLink(un)->message;
				adapter->request(message);
				base->getLink(un)->managment(field, (base->getAllUnits(adapter)), neutral, adapter);
			}
			else
				Sleep(1000);
		} break;
		case 3:
		{
			std::string fout = "save";
			Originator *org = new Originator(fout, false);
			Caretaker *ct = new Caretaker(org);
			Units *selectedUnit = NULL;
			int currNumBase = 1;
			org->restore(this, isUnitSelected, logToFile, logToTerminal, withoutLog, currNumBase);
		}break;
		case 4:
		{
			std::string fout = "save";
			Originator *org = new Originator(fout, true);
			Caretaker *ct = new Caretaker(org);
			Units *selectedUnit = NULL;
			int currNumBase = 1;
			org->save(this, isUnitSelected, logToFile, logToTerminal, withoutLog, selectedUnit, currNumBase);
		}break;
		case 5:
		{
			countermoves--;
			base->refresh();
			for (int i = 0; i < base->count_units; i++)
			{
				base->getLink(i + 1)->radius.refresh();
			}
			return;
		}break;
		case 6:
		{
			system("cls");
			game = Game<Rules>::get_game(rule);
		}break;
		default:
			cout << "Неккоректный ввод!";
			string message = "Пользователь ввёл некорректные данные";
			adapter->request(message);
			break;
		}
	}
	if (_countermoves_1 = 0 && rule->player_count == 1)
	{
		cout << "Игра закончена. Вы проиграли!";
		Sleep(1000);
		delete this;
	}
	if (_countermoves_1 == 0 && _countermoves_1 == 0 && (rule->player_count) == 2)
	{

	}
}



template <typename T>
int Game<T>::management(Adapter *adapter)
{
	//using namespace std;
	char choice = ' ';
	while (int(choice-'0') < 1 || int(choice - '0') > 6){
		try {
			string event[6] = { "Управление базой","Управление юнитом","Загрузить игру","Сохранить игру", "Закончить ход", "Новая игра" };
			for (int i = 0; i < 6; i++)
			{
				cout << (i + 1) << " - " << event[i] << endl;
			}
			cout << endl << "Выбор: ";
			cin >> choice;
			if (isdigit(choice)) {
				if (int(choice - '0') < 7 && int(choice - '0') > 0) {
					string message = "Пользователь выбрал " + event[int(choice - '0') - 1];
					adapter->request(message);
					break;
				}
				else {
					throw error2(choice);
					break;
				}
			}
			else throw error1(choice);
		}
		catch (error1& e)
		{
			cout << e.what();
			e.printErr();
			continue;
		}
		catch (error2& e)
		{
			cout << e.what();
			e.printErr();
			continue;
		}
	}
	return int(choice-'0');
}


template <typename T>
void Game<T>::choice_map(Adapter *adapter)
{
	char choice = ' ';
	while (choice != '1' && choice != '2' && choice != '3' && choice != '4') {
		try {
			string event[4] = { "Поле стандартного размера 20х20","Произвольное поле","Загрузить игру","Выход" };
			cout << "Выбор игрового поля:" << endl;
			for (int i = 0; i < 4; i++)
				cout << (i + 1) << " - " << event[i] << endl;
			cout << "Выбор: ";
			cin >> choice;
			string message;
			if (!isdigit(choice)) throw error1(choice);
			else {
				if (choice == '1' || choice == '2' || choice == '3' || choice == '4') {
					message = "Пользователь выбрал " + event[(choice - '0') - 1];
					adapter->request(message);
					cin.clear();
				}
				switch (choice) {
				case '1':
					_x_max = _y_max = 20;
					break;
				case '2':
				{
					cout << "Введите размер поля: ";
					string x = "fff";
					while (!(atoi(x.c_str()) <= 40 && atoi(x.c_str()) > 0)) {
						cout << "x_max: ";
						cin >> x;
					}
					_x_max = atoi(x.c_str());
					message = "Пользователь ввёл ширину поля, равную " + to_string(_x_max);
					adapter->request(message);
					string y = "fff";
					while (!(atoi(y.c_str()) <= 40 && atoi(y.c_str()) > 0)) {
						cin.clear();
						while (cin.get() != '\n');
						cout << "y_max: ";
						cin >> y;
					}
					_y_max = atoi(y.c_str());
					message = "Пользователь ввёл высоту поля, равную " + to_string(_y_max);
					adapter->request(message);
				}	break;
	
				case '3':
				{
					std::string fout = "save";
					Originator *org = new Originator(fout, false);
					Caretaker *ct = new Caretaker(org);
					Units *selectedUnit = NULL;
					int currNumBase = 1;
					org->restore(this, isUnitSelected, logToFile, logToTerminal, withoutLog, currNumBase);
				}
				case '4':
					cout << "Выход из программы.\n";
					exit(0);
				default:
					message = "Пользователь ввёл некорректные данные";
					adapter->request(message);
					throw error2(choice);
				}
			
			}
		}
		catch (error1& e)
		{
			cout << e.what();
			e.printErr();
			continue;
		}
		catch (error2& e)
		{
			cout << e.what();
			e.printErr();
			continue;
		}
	}
}



template <typename T>
int Game<T>::xMax()
{
	return _x_max;
}

template <typename T>
int Game<T>::yMax()
{
	return _y_max;
}

template <typename T>
bool Game<T>::typeRules()
{
	return _multiplayer;
}

template <typename T>
T* Game<T>::getRule()
{
	return rule;
}