#include "Proxy.h"

Proxy::Proxy(Landscape* l) {
	this->landsc = l;
}

Proxy::~Proxy() {
	delete landsc;
}

string Proxy::getLandscapeType() {
	if (landsc != nullptr) {
		return landsc->getLandscapeType();
	}
	return "No";
}

string Proxy::effectOfLndscp(Warrior w) {
	if (this->getLandscapeType() == "UnknownL") {
		return "yes";
	}

	return "no";
}

bool Proxy::canWalk2timesPerTurn(Warrior w) {
	if (w.GetValue()[0] == 'O') {
		if (this->getLandscapeType() == "burningE") return true;
	}

	else if (w.GetValue()[0] == 'E' || w.GetValue()[0] == 'M') {
		if (this->getLandscapeType() == "forest") return true;
	}

	return false;
}
