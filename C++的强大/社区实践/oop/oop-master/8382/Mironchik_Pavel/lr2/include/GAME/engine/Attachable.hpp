#pragma once

#include <cassert>
#include <memory>
#include <set>

using std::set;
using std::shared_ptr;

template<class Origin>
class Attachable {
private:
	Origin* _origin;

public:
	void attach(Origin* object) {
		assert(_origin == nullptr);
		_origin = object;
		onAttach(*object);
	}

	void detach() {
		assert(_origin != nullptr);
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