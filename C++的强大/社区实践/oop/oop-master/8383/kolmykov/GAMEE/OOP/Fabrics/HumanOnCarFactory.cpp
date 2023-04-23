#include "HumanOnCarFactory.h"



HumanOnCarFactory::HumanOnCarFactory()
{
	type = UnitType::HUMAN_ON_CAR;
    kind = Kind::HUMAN;
}


HumanOnCarFactory::~HumanOnCarFactory()
{
}

std::shared_ptr<Unit> HumanOnCarFactory::create(int x, int y, int level)
{
	return std::shared_ptr<Unit>(new HumanOnCar(x, y, level));
}


std::string HumanOnCarFactory::getPath() {
    return "humanOnCar.png";
}
