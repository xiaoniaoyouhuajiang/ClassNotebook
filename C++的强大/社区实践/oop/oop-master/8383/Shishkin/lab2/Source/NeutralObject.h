//#pragma once
#ifndef NEUTRALOBJECT_H
#define NEUTRALOBJECT_H

#include "Field.h"

using namespace std;

enum NeutralObject_ID { Health_ID = 0, Armor_ID, Killer_ID, Freezer_ID, NO_ID };

class NeutralObject {
public:
	virtual ~NeutralObject() = default;
	virtual void operator+=(Warrior* w) = 0;
	virtual string getNeutObjType() = 0;
	NeutralObject* create(NeutralObject_ID id);     //фабричный метод
};

class HealthReplenishment : public NeutralObject {      //пополнение здоровья
public:
	string getNeutObjType() override;
	void operator+=(Warrior* w) override;

};

class ArmorReplenishment : public NeutralObject {  //пополнение брони
public:
	string getNeutObjType() override;
	void operator+=(Warrior* w) override;

};

class Killer : public NeutralObject {  //здоровье стоящего на этом блоке юнита становится равно 5
public:
	string getNeutObjType() override;
	void operator+=(Warrior* w) override;

};

class Freezer : public NeutralObject {  //юнит не может двигаться на протяжении 2 ходов
public:
	string getNeutObjType() override;
	void operator+=(Warrior* w) override;

};

#endif