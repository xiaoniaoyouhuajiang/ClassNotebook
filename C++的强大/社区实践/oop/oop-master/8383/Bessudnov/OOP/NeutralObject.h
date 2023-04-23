#pragma once
#include "Interfaces.h"
#include "GameUtilities.h"
#include "UnitParent.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Vector2D;
class GameField;
class NeutralObjectContainer;

enum NeutralObjects {Apple = 6, Dew, Ligth, Branch};

class NeutralObject : public INeutralObjects{
private:
	int containerIndex;
	NeutralObjectContainer *container;
public:
	Vector2D location;
	NeutralObjects type;
	NeutralObject(NeutralObjectContainer *container, int index);
	NeutralObject() = default;
	~NeutralObject();

	void erraseObject();

	virtual void onExecute(UnitParent *unit) {};
};

class AppleObject : public NeutralObject {
public:
	AppleObject(NeutralObjectContainer *container, int index) : NeutralObject(container, index) {
		type = NeutralObjects::Apple;
	}
	
	void onExecute(UnitParent *unit);
};

class DewObject : public NeutralObject {
public:
	DewObject(NeutralObjectContainer *container, int index) : NeutralObject(container, index) {
		type = NeutralObjects::Dew;
	}

	void onExecute(UnitParent *unit);
};

class LigthObject : public NeutralObject {
public:
	LigthObject(NeutralObjectContainer *container, int index) : NeutralObject(container, index) {
		type = NeutralObjects::Ligth;
	}

	void onExecute(UnitParent *unit);
};

class BranchObject : public NeutralObject {
public:
	BranchObject(NeutralObjectContainer *container, int index) : NeutralObject(container, index) {
		type = NeutralObjects::Branch;
	}

	void onExecute(UnitParent *unit);
};


class NeutralObjectContainer {
private:
	NeutralObject *object;
	GameField *field;
public:
	std::vector<NeutralObject*> objects;

	class NObjectsContainerSnapshot {
	private:
		std::vector<NeutralObject*> objects;
	public:
		NObjectsContainerSnapshot(NeutralObjectContainer *nContainer);
		NObjectsContainerSnapshot() = default;

		std::vector<NeutralObject*> getNObjects();
		friend std::ofstream &operator<<(std::ofstream &os, NObjectsContainerSnapshot &snapshot);
		friend std::ifstream &operator>>(std::ifstream &is, NObjectsContainerSnapshot &snapshot);
	};


	NObjectsContainerSnapshot *saveObjects() {
		return new NObjectsContainerSnapshot(this);
	}

	NeutralObjectContainer(std::string fileName, GameField *field);
	NeutralObjectContainer() = default;
	NeutralObjectContainer(const NeutralObjectContainer *nObjects);

	void loadNObjects(NObjectsContainerSnapshot *nObjectsSnapshot);

	NeutralObject* getObjectAtLocation(Vector2D loc);
	void useObject(GameUnits &units);
	~NeutralObjectContainer();
	void addObject(Vector2D location, int Type);

	bool operator==(const GameUnits &units);
};

