#include "GunStrategy.h"
#include <iostream>
void GunStrategy::applyEffect(Unit*& target) {
	target->setAttackBuff(5);

}

void GunStrategy::removeEffect(Unit*& target) {

	target->setAttackBuff(0);
}