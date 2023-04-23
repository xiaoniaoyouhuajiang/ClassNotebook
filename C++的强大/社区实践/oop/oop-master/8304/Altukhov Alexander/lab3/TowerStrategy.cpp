#include "TowerStrategy.h"

void TowerStrategy::applyEffect(Unit*& target) {
	target->setArmorBuff(5);
}

void TowerStrategy::removeEffect(Unit * &target) {
	target->setArmorBuff(0);
}

void TowerStrategy::applyEffectForTimur(Unit& target) {
	target.setArmorBuff(5);
}

void TowerStrategy::removeEffectForTimur(Unit& target) {
	target.setArmorBuff(0);
}