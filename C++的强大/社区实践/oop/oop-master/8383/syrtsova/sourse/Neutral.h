#pragma once
#include "Object.h"
#include "Map.h"
#include "Dragon.h"

/// Класс Нейтральных объектов

/**
* Класс, содержащий информацию о нейтральных объектах
*/
class Neutral : public Object
{
	Neutral *link[4]; // Указатели на нейтральные объекты
	int _x_max; //Максимальный размер поля по Х
	int _y_max; //Макстмальный размер поля по Y
protected:
	char name; // Наименования нейтарльного объекта
/// Координаты нейтрального объекта
	struct Coordinates {
		int x, y;
	}XY;
public:
	/// Конструктор нейтрального объекта
	Neutral(char n, string message, int x_, int y_, int col);
	/// Виртуальная функция вывода сообщения 
	virtual void message() =  0;
	///Функция получения нейтрального объекта
	Neutral* returnThis(int x, int y);
	///Функция установки положения на карте 
	void setLoc(int x, int y);
	///Функция получения координаты по оси X
	int getX();
	///Функция получения координаты по оси Y
	int getY();
	Neutral* getLink(int &x, int &y);
};


/// Класс Таверны

/**
* Класс, содержащий информацию о таверне
*/
class Pab : public Neutral
{
public:
	Pab(int x, int y);
	void message() override; 
	~Pab();
};

/// Класс Таблички

/**
* Класс, содержащий информацию о табличке
*/
class Tablet : public Neutral
{
public:
	Tablet(int x, int y);
	void message() override;
	~Tablet();
};

/// Класс Замок

/**
* Класс, содержащий информацию о замке
*/
class Cave : public Neutral
{
public:
	Dragon* dragon;
	Cave(int x, int y);
	void message() override;
	~Cave();
};
/// Класс Руин

/**
* Класс, содержащий информацию о руинах
*/
class Ruin : public Neutral
{
	bool trap_1, trap_2, trap_3, trap_4, trap_5;
	int strength_1, strength_2, strength_3, strength_4, strength_5;
	bool state;
public:
	bool passage();
	void printMessage(string message);
	Ruin(int x, int y);
	void message() override;
	~Ruin();
};

/// Класс Создания нейтральных объектов

/**
* Класс, хранящий указатели на все нейтральные объекты и отвечающий за их создание
*/
class Creating 
{
public:
	Pab *pab;
	Tablet *tablet;
	Cave *cave;
	Ruin *ruin;
	Creating(int x_max, int y_max, Map* field);
	Creating(int x_max, int y_max, Map* field, bool state);
};