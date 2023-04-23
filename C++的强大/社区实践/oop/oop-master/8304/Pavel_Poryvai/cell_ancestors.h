#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include<vector>
#include <Windows.h>
#define nullptr NULL

using namespace std;

class foot {
protected:
	char e_weapon_foot[50];
public:
	foot() {

		std::cout << "\n\n Создаем объект пехота\n";

	}
	~foot() {

		std::cout << "Удаление объекта пехота\n\n";
	}



};

class archers {//Поменять название
protected:
	char e_weapon_luchniki[50];
public:

	archers() {

		std::cout << "Создаем объект лучники\n";
	}
	~archers() {

		std::cout << "Удаление объекта лучники\n";
	}
	//
};

class cavalry {
protected:
	char e_weapon_konnica[50];
public://
	cavalry() {

		std::cout << "Создаем объект конница\n";

	}
	~cavalry() {

		std::cout << "Удаление объекта конница\n";
	}
};


class unit :public foot, public archers, public cavalry {
protected:


	char* kind;
	int health;
	int attack_force;
	int paracetomol;
	char* type;//Вытащил тк не записывается через create_unit_of_base
public:

	char* get_type() {
		return type;
	};
	char* get_kind() {
		return kind;
	}

	int get_health() {
		return health;
	};

	int get_attack_force() {
		return attack_force;
	};
	void memory() {
		type = new char[100];
	}
	int get_paracetomol() {
		return paracetomol;
	};

	unit() {

		std::cout << "Создается объект юнит\n";
		//strcpy_s(type, 50, "Пустая клетка");

	};

	~unit() {

		std::cout << " Удаляется объект юнит\n";
	}


};
//lab2




struct units_location {

	int i = -1;
	int j =-1;


};


class base {//в клетке создается   база или юнит в базе создается юнит

	int health_base;
	int max_number_units_base;
	int units_i;//поле всегда обновляется (куда размещаем юнит
	units_location* location = nullptr;

public:

	base() {

		std::cout << " Создается класс базы\n";
		health_base = 10;
		max_number_units_base = 10;
		units_i = 0;
		location = new units_location[10];
	}

	base(int health, int max_number) {

		health_base = health;
		int max_number_units_base = max_number;
		units_i = 0;
		location = new units_location[max_number];

	}
	~base()
	{
		delete location;
	}
	//Методы создания юнитов

	bool create_unit_from_base(int i, int j) {//эта функция вызыается из playing_field 

		if (units_i + 1 <= max_number_units_base) {


			location[units_i] = { i,j };
			units_i++;

			return true;
		}
		else
			return false;



	}


	units_location* get_units_location() {

		return location;
	}

	int get_number_of_units() {

		return units_i;
	}

	void display_units(int i,int j ) {

		std::cout << "\nРасоложение юнитов от  базы на " << i << " " << j << ":\n";

		for (int i = 0; i < units_i; i++)
			std::cout << "\n" << location[i].i << " " << location[i].j << "\n";
	}



	
};


class cell :public unit, public base {



public:
	int write_in = 0;//0 в cell ничего нет 1 в cell юнит 2 в cell база 3 в cell база и от нее юнит
	cell() {

		std::cout << "Создается объект клетка \n\n";
		type = nullptr;
		kind = nullptr;
		write_in = 0;//Клетка пустая
		//strcpy_s(type, 50, "Пустая клетка");
	}

	cell(const cell& ob);//конструктор копии lvalue-reference
	//cell(cell && s);//rvalue-reference перемещающий конструктор
	//cell& operator=(cell && s);

	~cell() {//Для корректного удаления при выделении памяти под наследованый класс

		if (write_in == 1) {

			delete type;
			delete kind;
		}

		std::cout << "\n\nУдаление объекта клетки\n";
	}


	int is_writein() {
		return write_in;
	}

	bool operator==(cell& op2) {

		if (strcmp(this->type, op2.type) == 0 && strcmp(this->kind, op2.kind) == 0)
			return true;
		else
			return false;
	}

	void set(const char* type_s, const char* kind_s);

	cell operator=(const cell& ob);

	void remove() {

		if (write_in == 1) {
			delete kind;
			kind = NULL;
			delete type;
			type = NULL;
			write_in = 0;
			//for(int i = 0; i < ;)
		}
		else if (write_in == 0) {

			std::cout << "\nКлетка уже пуста\n";

		}

	}

	void remove(int i , int j) {

		if (write_in == 1) {
			delete kind;
			kind = NULL;
			delete type;
			type = NULL;
			write_in = 0;
			units_location* p = get_units_location();
			for (int k = 0; k < get_number_of_units(); k++) {
				
				if (p[k].i == i && p[k].j == j) {
					p[k].i = -1;
					p[k].j = -1;
				}
				
			}
		}
		else if (write_in == 0) {

			std::cout << "\nКлетка уже пуста\n";

		}

	}

};
