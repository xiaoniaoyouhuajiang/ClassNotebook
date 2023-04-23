#pragma once

#include <cassert>
#include <memory>
#include <set>

#include <GAME/serialize/InObjectsTable.hpp>
#include <GAME/serialize/OutObjectsTable.hpp>
#include <GAME/serialize/Serializer.hpp>
#include <GAME/log/Log.hpp>

using std::set;
using std::shared_ptr;
using std::istream;
using std::ostream;

template<class Origin>
class Attachable {
private:
	Origin* _origin = nullptr;

protected:
	void writeAttachable(ostream& os, OutObjectsTable& table) {
		ObjectInfo info;

		info = table.writeInfo(os, _origin);
		assert(!info.needWrite);
	}

	void readAttachable(istream& is, InObjectsTable& table) {
		ObjectInfo info;

		info = table.readInfo(is);
		assert(!info.needWrite);
		table.getObject(info, [this](void* obj) {
			this->_origin = (Origin*)obj;
		});
	}

public:
	virtual ~Attachable() {}

	void attach(Origin* object) {
		if (_origin != nullptr) {
			LogInfo info;
			info.name = "Attachable";
			info.pushParam("originType", typeid(Origin).name());
			info.pushParam("description", "Failed to attach: object is already attached");
			Log::exception(info);
		}

		_origin = object;
		onAttach(*object);
	}

	void detach() {
		if (_origin != nullptr) {
			LogInfo info;
			info.name = "Attachable";
			info.pushParam("originType", typeid(Origin).name());
			info.pushParam("description", "Failed to detach: object is not attached");
			Log::exception(info);
		}

		onDetach();
		_origin = nullptr;
	}

	bool isAttached() {
		return _origin != nullptr;
	}

	Origin* origin() {
		return _origin;
	}

	virtual void onAttach(Origin& object) {}
	virtual void onDetach() {}
};