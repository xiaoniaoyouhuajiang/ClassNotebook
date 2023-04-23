#pragma once
#include "Object.h"
#include "Map.h"

/// Класс Ландшавта

/**
* Класс, содержащий информацию о ландшавте
* Содержит ограничители типов ланшафта и функцию генерациии ланшафта
*/

class Land : public Object {
protected:
	/// Наименование
	char name;
	/// Максимальный размер карты
	int max_size;
	/// Ограничитель воды
	int max_water;
	/// Ограничитель земли 
	int max_grass;
	/// Ограничитель гор
	int max_stones;
	/// Высота и длина поля
	int  width, height;
	/// Координаты ландшафта
	int x, y;
public:
	/// Конструткор создания конкретного ландшафта
	Land(char N, int width, int height, int color);
	/// Функция генерации ландшафта
	void generation(Map* field);
	/// Деструктор класса
	~Land(){}
};
/// Класс Воды

/**
* Класс, содержащий информацию о водных ресурсах карты
*/
class Water : public Land {
	
public:
	Water(int width, int height, Map *field);
	~Water() {}
};

/// Класс Земли

/**
* Класс, содержащий информацию о водных ресурсах карты
*/
class Grass : public Land {
public:
	Grass(int width, int height, Map *field);
	~Grass() {}
};

/// Класс Гор

/**
* Класс, содержащий информацию о водных ресурсах карты
*/
class Stones : public Land {
public:
	Stones(int width, int height, Map *field);
	~Stones() {}
};

/// Класс Хранящий информацию ландшафта и отвечающий за корректную его генерацию 

/**
* Класс, содержащий информацию о ландшавте
* Содержит ограничители типов ланшафта и функцию генерациии ланшафта
*/

class Landscape 
{
	Grass *grass;
	Water *water;
	Stones *stones;
public:
	Landscape(int x_max, int y_max, Map* field);
	~Landscape() {}
};