//#pragma once
#ifndef UNITFACTORY_H
#define UNITFACTORY_H

//#include "Warrior.h"
#include "Orcs.h"
#include "Elfs.h"
#include "Men.h"

using namespace std;

class UnitFactory {
public:
	virtual Warrior createUnit(int x, int y, string value) = 0;
	virtual ~UnitFactory();
};

class ArcherFactory : public UnitFactory {
public:
	Warrior createUnit(int x, int y, string value);
};

class InvisibleFactory : public UnitFactory {
public:
	Warrior createUnit(int x, int y, string value);
};

class SpearmanFactory : public UnitFactory {
public:
	Warrior createUnit(int x, int y, string value);
};

class WizardFactory : public UnitFactory {
public:
	Warrior createUnit(int x, int y, string value);
};


class DevourerFactory : public UnitFactory {
public:
	Warrior createUnit(int x, int y, string value);
};

class RobberFactory : public UnitFactory {
public:
	Warrior createUnit(int x, int y, string value);
};

#endif