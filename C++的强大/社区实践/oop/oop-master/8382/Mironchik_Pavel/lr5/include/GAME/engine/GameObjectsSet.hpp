#pragma once

#include <set>
#include <memory>

using std::set;
using std::shared_ptr;

class GameObject;

class GameObjectsSetComparator {
public:
	bool operator()(const shared_ptr<GameObject>& ef1, const shared_ptr<GameObject>& ef2) const;
};

class GameObjectsSet : public set<shared_ptr<GameObject>, GameObjectsSetComparator> {
};