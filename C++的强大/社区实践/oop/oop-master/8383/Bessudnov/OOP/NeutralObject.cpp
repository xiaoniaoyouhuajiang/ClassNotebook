#include "pch.h"
#include "NeutralObject.h"
#include "GameUnits.h"
#include "GameField.h"
#include "UnitParent.h"
#include <fstream>
#include <iostream>
#include <algorithm>


NeutralObject::NeutralObject(NeutralObjectContainer *container, int index) : container(container), containerIndex(index) {
}


NeutralObject::~NeutralObject() {
}

void NeutralObject::erraseObject() {
	container->objects.erase(container->objects.begin() + containerIndex);
}

void NeutralObjectContainer::addObject(Vector2D location, int type) {
	int index = objects.size();
	switch (type) {
	case NeutralObjects::Apple:
		objects.push_back(new AppleObject(this, index));
		break;
	case NeutralObjects::Branch:
		objects.push_back(new BranchObject(this, index));
		break;
	case NeutralObjects::Dew:
		objects.push_back(new DewObject(this, index));
		break;
	case NeutralObjects::Ligth:
		objects.push_back(new LigthObject(this, index));
		break;
	default:
		break;
	}
	objects.back()->location = location;
	field->getBlockAtLocation(location)->setObject(objects.back());
}

NeutralObjectContainer::NeutralObjectContainer(std::string fileName, GameField *field) : field(field) {
	std::ifstream ifs;
	ifs.open(fileName, std::ifstream::in);
	int size;
	ifs >> size;

	int type;
	int x;
	int y;
	for (int i = 0; i < size; i++) {
		ifs >> type;
		ifs >> x >> y;
		addObject(Vector2D(x, y), type);
	}
}

NeutralObjectContainer::NeutralObjectContainer(const NeutralObjectContainer *nObjects) {
}

void NeutralObjectContainer::loadNObjects(NeutralObjectContainer::NObjectsContainerSnapshot *nObjectsSnapshot) {
	std::vector<NeutralObject*> loadObjects = nObjectsSnapshot->getNObjects();
	objects.clear();
	for (auto &obj : loadObjects) {
		addObject(obj->location, obj->type);
	}

	for (auto &obj : objects) {
		field->getBlockAtLocation(obj->location)->setObject(obj);
	}
}

NeutralObject *NeutralObjectContainer::getObjectAtLocation(Vector2D loc) {
	for (auto &obj : objects) {
		if (obj->location == loc) return obj;
	}
	return nullptr;
}

void NeutralObjectContainer::useObject(GameUnits &units) {
	for (size_t i = 0; i < objects.size(); i++) {
		if (object == objects[i]) {
			objects.erase(objects.begin() + i);
			return;
		}
	}
}

NeutralObjectContainer::~NeutralObjectContainer() {
	objects.clear();
	delete object;
}

bool NeutralObjectContainer::operator==(const GameUnits &units) {
	object = getObjectAtLocation(units.units[units.currentUnitIndex]->unitProps.location);
	if (object != nullptr) {
		return true;
	}

	return false;
}

void AppleObject::onExecute(UnitParent *unit) {
	std::cout << "It's APPLE" << std::endl;
}

void DewObject::onExecute(UnitParent *unit) {
	unit->unitProps.dew.increasePar(3);
}

void LigthObject::onExecute(UnitParent *unit) {
	unit->unitProps.ligth.increasePar(3);
}

void BranchObject::onExecute(UnitParent *unit) {
	unit->unitProps.moves.increasePar(3);
}

NeutralObjectContainer::NObjectsContainerSnapshot::NObjectsContainerSnapshot(NeutralObjectContainer *nContainer) {
	objects.resize(nContainer->objects.size());
	std::copy(nContainer->objects.begin(), nContainer->objects.end(), objects.begin());
}

std::vector<NeutralObject*> NeutralObjectContainer::NObjectsContainerSnapshot::getNObjects() {
	return objects;
}

std::ofstream & operator<<(std::ofstream & os, NeutralObjectContainer::NObjectsContainerSnapshot & snapshot) {
	os << snapshot.objects.size() << std::endl;
	for (auto &obj : snapshot.objects) {
		os << obj->type << " ";
		os << obj->location << std::endl;
	}
	return os;
}

std::ifstream & operator>>(std::ifstream & is, NeutralObjectContainer::NObjectsContainerSnapshot & snapshot) {
	int objectsAmount;
	is >> objectsAmount;
	snapshot.objects.resize(objectsAmount);
	for (auto &obj : snapshot.objects) {
		obj = new NeutralObject;
		int objType;
		is >> objType;
		obj->type = static_cast<NeutralObjects>(objType);
		is >> obj->location;
	}
	return is;
}
