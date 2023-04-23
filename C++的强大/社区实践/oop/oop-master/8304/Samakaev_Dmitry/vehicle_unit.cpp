#include "vehicle_unit.h"

Siege_tower::Siege_tower() {
	type = unitType::Siege_tower;
	name = 'T';
	hp.change(50);
	armor.change(100);
}

Catapult::Catapult() {
	type = unitType::Catapult;
	name = 'C';
	hp.change(50);
	damage.change(40);
	armor.change(30);
}