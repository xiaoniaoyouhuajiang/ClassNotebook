#pragma once

#include <iostream>
#include <set>

#include <GAME/serialize/ObjectInfo.hpp>
#include <GAME/serialize/Serializer.hpp>

using std::ostream;
using std::set;

class OutObjectsTable {
private:
	set<ObjectInfo> _writtenObjects;

public:
	ObjectInfo writeInfo(ostream& os, const void* object) {
		ObjectInfo info;
		info.object = object;
		info.needWrite = _writtenObjects.find(info) == _writtenObjects.end() && object != nullptr;
		Serializer::writeObjectInfo(os, &info);

		if (info.needWrite)
			_writtenObjects.insert(info);

		return info;
	}
};