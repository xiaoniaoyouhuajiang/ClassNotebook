#pragma once
#include "Naming.h"
#include "IUnit.h"

class ILandscape{
public:
	virtual Landscapes typeOfLandscape() = 0;
};

class Hill : public ILandscape {
public:
	Landscapes typeOfLandscape() override;
	Hill() = default;
};

class Plain : public ILandscape {
public:
	Landscapes typeOfLandscape() override;
	Plain() = default;
};

class Lake : public ILandscape {
public:
	Landscapes typeOfLandscape() override;
	Lake() = default;
};

class FabricOfLandscape {
public:
	ILandscape* creatorLandsacpe(Landscapes type) {
		switch (type){
		case HILL:
			return new Hill();
		case PLAIN:
			return new Plain();
		case LAKE:
			return new Lake();
		default:
			return nullptr;
		}
	}
};

class Proxy : public ILandscape {
private:
	ILandscape* landscape;
	Landscapes type;
public:
	Proxy(ILandscape* l);
	bool doSomething(IUnit* build);
	Landscapes typeOfLandscape() override;
};