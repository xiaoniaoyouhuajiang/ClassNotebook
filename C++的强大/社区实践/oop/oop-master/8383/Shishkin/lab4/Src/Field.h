//#pragma once
#ifndef FIELD_H
#define FIELD_H

//#include "Warrior.h"
#include "Orcs.h"
#include "Men.h"
#include "Elfs.h"
#include "NeutralObject.h"
//#include "Landscape.h"
#include "UnitFactory.h"
#include "Cell.h"
#include "Proxy.h"
#include "Mediator.h"
//#include "Command.h"
#include "LoggerProxy.h"

class Proxy;
class Command;

using namespace std;

class Field {
public:
	Field();
	Field(int a, int numOfUnitsOnEachSide, LoggerProxy* logger);
	~Field();        //деструктор
	Field(const Field& f);        //конструктор копирования
	Field(Field&& f);           //конструктор перемещения
	void mas();          //создает массив cell
	void print();             //печатает поле
	void init(int numOfOrcs, int numOfElfs, int numOfMens);     //инициализирует поле
	void moving(string& character, int direction);     //двигает юнит character в направление direction
	string check(string& character);            //проверка на то, в какакие направление может ходить юнит character
	void unitsSpecAbil(int dir, Warrior w, int x, int y);    //специальные возможности юнитов в атаке
	Warrior add(string& character, int coordx, int coordy);      //добавить юнит
	void del(string& character);          //удалить юнит
	void changeCell(string& valuee, int x, int y);      //поменять значение в клетке в координатах (x; y)
	bool isCellFree(int x, int y);       //пустая ли клетка в координатах (x; y)
	string getValueInCell(int x, int y);   //возвращает значение, хранящаеся в cell[x][y]
	Cell** getCell();            //возвращает клетку
	int howManyMoves(string character);       //возвращает количество шагов, которое можно сделать игроку
	void landscapeEffect();     //эффект "неизвестных земель"
	void neutObjEffect();      //эффект нейтральных объектов
	int getSizeOfField();    //возвращает размер поля

private:
	int size;
	Cell** cell;

	Devourers dev;
	Robbers rob;

	Spearman sp;
	Wizard wiz;

	Archer ar;
	Invisible inv;

	int current1stPlayerUnits;         //текущее количество юнитов у 1-го игрока
	int current2ndPlayerUnits;         //текущее количество юнитов у 2-го игрока
	Mediator* med;
	LoggerProxy* logger;
};


#endif
