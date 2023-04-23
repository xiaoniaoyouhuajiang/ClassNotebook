#pragma once
#include "IUnit.h"
#include "Naming.h"

class Dacha : public Apartment {
public:
	Builds typeOfBuild() override;
	Dacha();
};

class Hrushchovka :public Apartment {
public:
	Builds typeOfBuild() override;
	Hrushchovka();
};

class Ferma :public Production {
public:
	Builds typeOfBuild() override;
	Ferma();
};

class Office :public Production {
public:
	Builds typeOfBuild() override;
	Office();
};

class Vodokanal :public Services {
public:
	Builds typeOfBuild() override;
	Vodokanal();
};

class School :public Services {
public:
	Builds typeOfBuild() override;
	School();
};

class Powerhouse :public Services {
public:
	Builds typeOfBuild() override;
	Powerhouse();
};

class FactoryOfBuildings {
public:
	Building* creator(Builds typeOfB);
};