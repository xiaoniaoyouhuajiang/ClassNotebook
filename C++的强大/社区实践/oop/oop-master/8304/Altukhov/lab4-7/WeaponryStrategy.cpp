#include "WeaponryStrategy.h"
void WeaponryStrategy::applyEffect(Unit*& target) {
	target->setRangeBuff(1);
}

void WeaponryStrategy::removeEffect(Unit*& target) {
	target->setRangeBuff(0);
}

void WeaponryStrategy::applyEffectForTimur(Unit& target) {
	target.setRangeBuff(1);
}

void WeaponryStrategy::removeEffectForTimur(Unit& target) {
	target.setRangeBuff(0);
}