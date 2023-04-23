#pragma once
#include "pch.h"
#include "Object.h"
#include <iostream>

#define MAX 4000

using namespace std;



/// Класс Карты

/**
* Класс, содержащий информацию о карте, включает различный набор функционала для взаимодействия с картой
*/
class Map {
	int  _width;   //размеры поля
	int  _height;   //размеры поля
	int  _count_object;//количество объектов
	int  _mas_x[MAX];  //массив координат x элементов на поле
	int  _mas_y[MAX];  //массив координат y элементов на поле
public:
	int getWidth(); // Получение ширины поля
	int getHeight(); // Получние высоты поля
	Object ***field;    //само поле
	Map(int &x, int &y); //конструктор
	bool isObject(int &x, int &y); // Проверка: является ли выбранный объект объектом
	Map(const Map & map); //конструктор копирования поля
	Map &operator=(const Map &map);//оператор для конструктора копирования
	Map(Map&& map);
	Map& operator=(Map&& map);
	void refreshMap(int &x, int &y, bool flag, Object *obj = new Object('*'));
	void printMap(); //выводит поле
	void addOnMap(int x, int y, Object* object);//добавляет объект
	void removeFromMap(int x, int y);//удаляет с поля объект
	int isLandscape(int &x, int &y); // Проверка: является ли выбранный объект ландшафтом
	int isNeutral(int x, int y);// Проверка: является ли выбранный объект нейтральным объектом
	bool isUnit(int x, int y); // Проверка: является ли выбранный объект юнитом
	bool isBase(int &x, int &y);// Проверка: является ли выбранный объект базой
	bool isLava(int x, int y);// Проверка: является ли выбранный объект лавой
	Object* getObject(int x, int y);// Получение объекта по его координатам
	~Map();
};


