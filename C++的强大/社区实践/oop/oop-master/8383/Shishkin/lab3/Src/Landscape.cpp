#include "Landscape.h"

Landscape* Landscape::create(Landscape_ID id) {
	//Forest_ID, BurningEarth_ID, UnknownLand_ID
	Landscape* l;

	switch (id) {
	case Forest_ID:
		l = new Forest();
		break;

	case BurningEarth_ID:
		l = new BurningEarth();
		break;

	case UnknownLand_ID:
		l = new UnknownLand();
		break;

	default:
		l = nullptr;
	}

	return l;
}

//-----------------------------------------------------------

string Forest::getLandscapeType() {
	return "forest";
}

string Forest::effectOfLndscp(Warrior w) {
	return "no";
}

bool Forest::canWalk2timesPerTurn(Warrior w) {
	if (w.GetValue()[0] == 'M' || w.GetValue()[0] == 'E')
		return true;
	return false;
}

//-----------------------------------------------------------

string BurningEarth::getLandscapeType() {
	return "burningE";
}

string BurningEarth::effectOfLndscp(Warrior w) {
	return "no";
}

bool BurningEarth::canWalk2timesPerTurn(Warrior w) {
	if (w.GetValue()[0] == 'O')
		return true;
	return false;
}

//-----------------------------------------------------------

string UnknownLand::getLandscapeType() {
	return "UnknownL";
}

string UnknownLand::effectOfLndscp(Warrior w) {
	return "no";
}

bool UnknownLand::canWalk2timesPerTurn(Warrior w) {
	return false;
}
