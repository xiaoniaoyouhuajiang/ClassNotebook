#pragma once

#include <set>
#include <memory>

using std::set;
using std::shared_ptr;

template<class T>
class SharedComparator {
public:
	bool operator()(const shared_ptr<T>& ef1, const shared_ptr<T>& ef2) const {
		return ef1 < ef2;
	}
};

template<class T>
class SharedSet : public set<shared_ptr<T>, SharedComparator<T>> {
};