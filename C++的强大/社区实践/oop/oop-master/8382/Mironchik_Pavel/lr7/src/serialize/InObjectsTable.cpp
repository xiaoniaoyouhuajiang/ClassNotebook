#include <cassert>

#include <GAME/serialize/InObjectsTable.hpp>
#include <GAME/serialize/Serializer.hpp>

InObject::InObject(ObjectInfo info, void* ptr) : info(info), ptr(ptr) {}

ObjectInfo InObjectsTable::readInfo(istream& is) {
	ObjectInfo info;
	Serializer::readObjectInfo(is, &info);
	return info;
}

void InObjectsTable::setObject(ObjectInfo& info, void* object) {
	_readObjects[info] = object;

	if (_callbacks.count(info)) {
		for (function<void(void*)>& callback : _callbacks[info])
			callback(object);

		_callbacks.erase(info);
	}
}

void InObjectsTable::getObject(ObjectInfo& info, function<void(void*)> callback) {
	if (info.object == nullptr) {
		callback(nullptr);
		return;
	}

	if (_readObjects.count(info)) {
		callback(_readObjects[info]);
		return;
	}

	if (!_callbacks.count(info))
		_callbacks[info] = list<function<void(void*)>>();

	_callbacks[info].push_back(callback);
}