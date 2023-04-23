#pragma once
#include "Nstrategy.h"


class Nobjects
{
protected:
	char name;
public:
	char getName();
	virtual void operator()(Unit*) = 0;

};

class HillingSatue : public Nobjects
{
	HillingStrategy strategy;
public:
	HillingSatue();
	void operator()(Unit*);
};

class ArmorStatue : public Nobjects
{
	ArmorStrategy strategy;
public:
	ArmorStatue();
	void operator()(Unit*);
};

class DamageStatue : public Nobjects
{
	DamageStrategy strategy;
public:
	DamageStatue();
	void operator()(Unit*);
};

class BigStatue : public Nobjects
{
	DamageStrategy  strategy1;
	ArmorStrategy   strategy2;
	HillingStrategy strategy3;
public:
	BigStatue();
	void operator()(Unit*);
};