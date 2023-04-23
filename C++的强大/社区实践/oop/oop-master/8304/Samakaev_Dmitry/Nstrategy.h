#pragma once
#include "unit_base.h"

class Strategy
{
public:
	virtual void get(int n, Unit*) = 0;
};

class HillingStrategy : public Strategy
{
public:
	void get(int n, Unit*);
};

class ArmorStrategy : public Strategy
{
public:
	void get(int n, Unit*);
};

class DamageStrategy : public Strategy
{
public:
	void get(int n, Unit*);
};
