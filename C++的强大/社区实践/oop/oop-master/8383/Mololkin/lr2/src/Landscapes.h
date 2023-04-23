#pragma once
#include "IUnit.h"

enum class Landscapes {
	SWAMP,
	PLAIN,
	HILLS,
};

class ILandscape {
public:
	virtual Landscapes getLandscapeType() = 0;
	virtual bool canGo() = 0;
};

class Swamp : public ILandscape {
private:
	Landscapes lendScapeType = Landscapes::SWAMP;
public:
	Landscapes getLandscapeType() override;
	Swamp() {};
	bool canGo() override;
};

class Plain : public ILandscape {
private: 
	Landscapes lendScapeType = Landscapes::PLAIN;
public:
	Landscapes getLandscapeType() override;
	Plain() {};
	bool canGo() override;
};

class Hills : public ILandscape {
private:
	Landscapes lendScapeType = Landscapes::HILLS;
public:
	Landscapes getLandscapeType() override;
	Hills() {};
	bool canGo() override;
};

class LandscapeFabric {
public:
	static ILandscape* getNewLandscape(Landscapes type);
};

class LandscapeProxy {
private:
	ILandscape* landscape;
public:
	LandscapeProxy(Landscapes landscapeType);
	Landscapes getLandscapeType();
	bool canGo();
	void landscapeInfluence(IUnit* unit);
};