#include "UnitFactory.h"

UnitFactory::~UnitFactory() {

}

Warrior ArcherFactory::createUnit(int x, int y, string value) {
	Archer ar;
	ar.SetPlaceX(x);
	ar.SetPlaceY(y);
	ar.SetValue(value);
	return ar;
}

Warrior InvisibleFactory::createUnit(int x, int y, string value) {
	Invisible inv;
	inv.SetPlaceX(x);
	inv.SetPlaceY(y);
	inv.SetValue(value);
	return inv;
}

Warrior SpearmanFactory::createUnit(int x, int y, string value) {
	Spearman sp;
	sp.SetPlaceX(x);
	sp.SetPlaceY(y);
	sp.SetValue(value);
	return sp;
}

Warrior WizardFactory::createUnit(int x, int y, string value) {
	Wizard wiz;
	wiz.SetPlaceX(x);
	wiz.SetPlaceY(y);
	wiz.SetValue(value);
	return wiz;
}

Warrior DevourerFactory::createUnit(int x, int y, string value) {
	Devourers dev;
	dev.SetPlaceX(x);
	dev.SetPlaceY(y);
	dev.SetValue(value);
	return dev;
}

Warrior RobberFactory::createUnit(int x, int y, string value) {
	Robbers rob;
	rob.SetPlaceX(x);
	rob.SetPlaceY(y);
	rob.SetValue(value);
	return rob;
}