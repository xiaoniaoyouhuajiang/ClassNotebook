#include "Neutral.h"
#include "NeutralFactory.h"

NeutralFactory::~NeutralFactory(){}

NeutralObject* PosionFactory::createObject(int x, int y) {
	DeadlyPosion* posion = new DeadlyPosion;
	posion->x = x;
	posion->y = y;
	return posion;
}

NeutralObject* KnivesFactory::createObject(int x, int y) {
	KnivesOut* knife = new KnivesOut;
	knife->x = x;
	knife->y = y;
	return knife;
}

NeutralObject* ArrowFactory::createObject(int x, int y) {
	ArrowsOut* arrow = new ArrowsOut;
	arrow->x = x;
	arrow->y = y;
	return arrow;
}

NeutralObject* DoubleFactory::createObject(int x, int y) {
	DoubleAttack* obj = new DoubleAttack;
	obj->x = x;
	obj->y = y;
	return obj;
}

NeutralObject* PlusFactory::createObject(int x, int y) {
	PlusDamage* obj = new PlusDamage;
	obj->x = x;
	obj->y = y;
	return obj;
}