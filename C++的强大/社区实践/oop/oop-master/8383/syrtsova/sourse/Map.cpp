#include "pch.h"
#include "Map.h"
#include <Windows.h>
#include <iostream>
#include "Object.h"



Map::Map(int &x, int &y) { //конструктор
	_count_object = 0;
	//_width = x;
	_width = 2 * x + 3;
	//_height = y;
	_height = y + 2;
	Object *line = new Object();
	Object* o = new Object(' ');
	field = new Object**[_height];
	for (int i = 0; i < _height; i++) {
		field[i] = new Object*[_width];
		for (int j = 0; j < _width; j++) {
			if ((i == 0 || i == _height - 1 || j == 0 || j == _width-1) && (j % 2 == 0)) field[i][j] = line;
			else field[i][j] = o;
		}
	}
	//createIterator();
}

Map::Map(Map&& map) : field(map.field)
{
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			map.field[i][j] = nullptr;
}

Map::Map(const Map & map) { //конструктор копирования поля
	_count_object = map._count_object;
	_width = map._width;
	_width = map._width;
	field = new Object**[_height];
	for (int i = 0; i < _height; i++)
		field[i] = new Object*[_width];
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			field[i][j] = map.field[i][j];
}

Map& Map::operator=(Map&& map)
{
	// Проверка на самоприсваивание
	if (&map == this)
		return *this;
	// Удаляем всё, что может хранить указатель до этого момента
	for (int i = 0; i < _height; i++) {
		delete field[i];
	}
	delete field;
	// Передаём право собственности на map.field в field
	field = map.field;
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width; j++)
			map.field[i][j] = nullptr;
	return *this;
}

Map &Map::operator=(const Map &map) {//оператор для конструктора копирования
	if (&map == this)
		return *this;
	// Проверка на самоприсваивание
	Object* o = new Object(' ');
	// Удаляем всё, что может хранить указатель до этого момента
	for (int i = 0; i < _height; i++) {
		delete field[i];
	}
	delete field;
	// Копируем передаваемый объект
	field = new Object **[_height];
	for (int i = 0; i < _height; i++) {
		field[i] = new Object *[_width];
		for (int j = 0; j < _width; j++) {
			field[i][j] = o;
		}

	}
	for (int k = 0; k < _height; ++k) {
		for (int i = 0; i < _width; ++i) {
			field[k][i] = map.field[k][i];
		}
	}
	return *this;
}

void Map::printMap() {
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), field[i][j]->color);
			cout << field[i][j]->object;
		}
		cout << endl;
	}
	cout << endl;
}

void Map::addOnMap(int x, int y, Object* object) {
	if (_count_object >= MAX) {//инвариант
		cout << "Превышено максимальное количество объектов на поле" << endl;
		exit(0);
	}
	else {
		for (int i = 1; i < _height - 1; i++) {
			for (int j = 1; j < _width - 1; j++) {
				if (i == y && j == 2 * x) 
				{ field[i][j] = object; }
				_mas_x[_count_object] = x;
				_mas_y[_count_object] = y;
			}
		}
		_count_object++;
	}
}

void Map::removeFromMap(int x, int y) {
	Object* g = new Object('*');
	g->color = g->colorLand::green;
	for (int i = 1; i < _height - 1; i++)
		for (int j = 1; j < _width - 1; j++) {
			if (i == y && j == 2 * x) {
				if (isObject(i,j)) {
					_count_object--; 
					field[i][j] = g;
					_mas_x[_count_object] = 0;
					_mas_y[_count_object] = 0;
				}
			}
		}
}

void Map::refreshMap (int &x, int &y, bool flag, Object *obj)
{
	if (flag)
		obj->color = obj->colorLand::green;
	for (int i = 1; i < _height - 1; i++)
		for (int j = 1; j < _width - 1; j++) {
			if (i == y && j == 2 * x) {
				HANDLE hOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);
				COORD coord = { j , i };
				::SetConsoleCursorPosition(hOutput, coord);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), field[i][j]->color);
				::WriteConsoleA(hOutput, obj, 1, NULL, NULL);
				coord = { 0,0 };
				::SetConsoleCursorPosition(hOutput, coord);
			}
		}
}

bool Map::isObject(int &x, int &y)
{
	Object* o = new Object(' ');
	if (field[x][y]->object != o->object)
		return true;
	else
		return false;
}

int Map::isLandscape(int &x, int &y)
{
	char list[] = { '~', '*', '^'};
	for (int i = 0; i < _height; i++)
		for (int j = 0; j < _width + 1; j++)
			if (i == y && j == 2 * x)
				for (int t = 0; t < sizeof(list); t++)
				{
					if (i == 0 || j == 0 || j == (_width - 1) || i == (_height - 1))
						return 4;
					if (field[i][j]->object == list[t])
						return t + 1;
				}	
	return 0;
}

int Map::isNeutral(int x, int y)
{
	char list[] = { 'P', 'T', 'C', 'R' };
	for (int i = 1; i < _height - 1; i++)
		for (int j = 1; j < _width - 1; j++)
			if (i == y && j == 2 * x)
				for (int k = 0; k < sizeof(list); k++)
					if (field[i][j]->object == list[k])
						return ++i;
	return 0;
}


bool Map::isLava(int x, int y)
{
	char o = '@';
	for (int i = 1; i < _height - 1; i++)
		for (int j = 1; j < _width - 1; j++)
			if (i == y && j == 2 * x)
				if (field[i][j]->object == o)
					return true;
				else
					return false;
}


bool Map::isUnit(int x, int y)
{
	char list[] = { 'X', 'H', 'M', 'A', 'F', 'G', 'L' };
	for (int i = 1; i < _height - 1; i++)
		for (int j = 1; j < _width - 1; j++)
			if (i == y && j == 2 * x)
				for (int k = 0; k < sizeof(list); k++)
					if (field[i][j]->object == list[k])
						return true;
	return false;
}

bool Map::isBase(int &x, int &y)
{
	for (int i = 1; i < _height - 1; i++)
		for (int j = 1; j < _width - 1; j++)
			if (i == y && j == 2 * x)
				if (field[i][j]->object == 'B')
					return true;
		return false;
}


int Map::getHeight()
{
	return _height;
}

int Map::getWidth()
{
	return _width;
}

Object* Map::getObject(int x, int y)
{
	return field[x][y];
}

Map::~Map() { //деструктор
	for (int i = 0; i < _height; i++)
		delete field[i];
	delete field;
}



