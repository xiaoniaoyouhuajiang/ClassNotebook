#include "CannonStrategy.h"
#include <iostream>
void CannonStrategy::applyEffect(Unit*& target) {
	target->setAttackBuff(5);

}

void CannonStrategy::removeEffect(Unit*& target) {

	target->setAttackBuff(0);
}

void CannonStrategy::applyEffectForTimur(Unit& target) {
	target.setAttackBuff(5);
}

void CannonStrategy::removeEffectForTimur(Unit& target) {
	target.setAttackBuff(0);
}