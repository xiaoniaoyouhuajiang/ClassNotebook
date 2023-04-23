#include <GAME/engine/GameObjectsSet.hpp>
#include <GAME/engine/GameObject.hpp>

bool GameObjectsSetComparator::operator()(const shared_ptr<GameObject>& ef1, const shared_ptr<GameObject>& ef2) const {
	return ef1->id() < ef2->id();
}