#pragma once
#include "unit_base.h"
#include "LandscapeResources.h"


class LandscapeIntefrace
{
public:
	virtual void setEffect(Unit*) = 0;
};


class DesertLandscape : public LandscapeIntefrace
{
public:
	void setEffect(Unit*);
};


class MountainLandscape : public LandscapeIntefrace
{
public:
	void setEffect(Unit*);
};


class SwampLandscape : public LandscapeIntefrace
{
public:
	void setEffect(Unit*);
};


class LandscapeProxy : public LandscapeIntefrace
{
private:
	LandscapeIntefrace* cur;

public:
	LandscapeProxy(LandscapeType);

	void setEffect(Unit*);

};