#include "Mediator.h"

Mediator::Mediator(Field* f) {
	this->f = f;
}

void Mediator::attack(Warrior w1, Warrior& w2) {
	w2.SetHealth(w2.GetHealth() - w1.GetDamage());

	if (w2.GetHealth() <= 0) {
		w2.SetValue("---");
		//w2.~Warrior();
	}
}