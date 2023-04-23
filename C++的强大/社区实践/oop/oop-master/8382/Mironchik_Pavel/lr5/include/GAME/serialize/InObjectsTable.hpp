#pragma once

#include <iostream>
#include <set>
#include <list>
#include <map>
#include <functional>

#include <GAME/serialize/ObjectInfo.hpp>

using std::istream;
using std::set;
using std::list;
using std::map;
using std::function;

class InObject {
public:
	ObjectInfo info;
	void* ptr;

	InObject(ObjectInfo id, void* ptr);

	bool operator==(InObject& other) {
		return info == other.info;
	}
};

class InObjectsTable {
private:
	map<ObjectInfo, void*> _readObjects;
	map<ObjectInfo, list<function<void(void*)>>> _callbacks;

public:
	ObjectInfo readInfo(istream& is);
	void setObject(ObjectInfo& info, void* object);
	void getObject(ObjectInfo& info, function<void(void*)> callback);
};