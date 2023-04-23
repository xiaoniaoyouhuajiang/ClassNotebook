#include "BaseFlyWeight.h"


void UnitNum::setUnitNum(int num) { 
	unitNum = num;
}

int UnitNum::getUnitNum() {
	return unitNum;
}

//--------------------------------------------------------

UnitNum* FlyweightUnitFactory::getUnitNum(int num) {

	for (int i = 0; i < units.size(); i++) {

		if (num == units[i]->getUnitNum())
			return units[i];
	}

	UnitNum* a = new UnitNum();
	a->setUnitNum(num);

	units.push_back(a);

	return units[units.size() - 1];

}
