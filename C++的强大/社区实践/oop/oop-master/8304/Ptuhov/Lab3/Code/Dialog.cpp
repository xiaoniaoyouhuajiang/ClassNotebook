#include "Dialog.h"

Dialog::Dialog()
{
	startCommands.push_back("1) Work with base");
	startCommands.push_back("2) Work with already created units");
	startCommands.push_back("3) Show field");
	startCommands.push_back("4) Quit");

	unitCommands.push_back("1) Create unit");
	unitCommands.push_back("2) Remove unit");
	unitCommands.push_back("3) Move unit");
	unitCommands.push_back("4) Unit characteristic");

	baseCommands.push_back("1) Create base-unit");
	baseCommands.push_back("2) Use base-boost");
	baseCommands.push_back("3) Set max units count");
	
	Field fld2(20, 20);
	fld = fld2;
	addTail = std::make_shared<AddCoordCheck>();
	removeTail = std::make_shared<RemoveCoordCheck>();
	mucTail = std::make_shared<PositivelyCheck>();
}

void Dialog::speak()
{
	std::cout << "Field size - 20x20\n\n";

	while (true)
	{
		for (auto& str : startCommands)
			std::cout << str << '\n';

		int choise = 3;
		std::cout << "\n" << "Enter command number: ";
		std::cin >> choise;

		switch (choise)
		{
		case 1:
			speakAboutBase();
			break;
		case 2:
			speakAboutUnits();
			break;
		case 3:
			showField();
			break;
		case 4:
			return;
		default:
			break;
		}

		std::cout << "\n\n";
	}
	
}

void Dialog::speakAboutUnits()
{
	for (auto& str : unitCommands)
		std::cout << str << '\n';

	int choise = 5;
	std::cout << "\n" << "Enter command number: ";
	std::cin >> choise;

	switch (choise)
	{
	case 1:
		createFiledUnit();
		break;
	case 2:
		removeFieldUnit();
		break;
	case 3:
		moveFieldUnit();
		break;
	case 4:
		characteristicFieldUnit();
		break;

	default:
		break;
	}

}

void Dialog::createFiledUnit()
{
	Point p;

	std::cout << "\nEnter coordinates: ";
	std::cin >> p.x >> p.y;
	std::cout << "\n";

	bool f = addBase(p);
	if (f == false)
		return;

	writeUnitsLegend();

	char type = 0;
	std::cout << "Enter unit type(1 symbol): ";
	std::cin >> type;
	std::cout << "\n";

	std::shared_ptr<UnitFactory> unf3 = std::make_shared<Tier3Factory>();
	std::shared_ptr<UnitFactory> unf2 = std::make_shared<Tier2Factory>();
	std::shared_ptr<UnitFactory> unf1 = std::make_shared<Tier1Factory>();
	std::shared_ptr<UnitBase> unit;

	switch (type)
	{
	case 'S':
		unit = unf3->createType1();
		break;
	case 'W':
		unit = unf3->createType2();
		break;
	case 'M':
		unit = unf1->createType1();
		break;
	case 'X':
		unit = unf1->createType2();
		break;
	case 'A':
		unit = unf2->createType1();
		break;
	case 'R':
		unit = unf2->createType2();
		break;
	default:
		std::cout << "Incorrect type\n";
		return;
	}

	fld.addUnit(unit, p);
	std::cout << "Unit added\n";
}

void Dialog::removeFieldUnit()
{
	Point p;

	std::cout << "Enter coordinates: ";
	std::cin >> p.x >> p.y;
	std::cout << "\n";

	addAndRemoveResult res = removeTail->check(fld, p.x, p.y);

	switch (res)
	{
	case addAndRemoveResult::removeErrorIncorrectCoord:
		std::cout << "Uncorrect coordinates\n";
		return;
	case addAndRemoveResult::removeErrorNoUnit:
		std::cout << "Here is no unit\n";
		return;
	case addAndRemoveResult::unitRemoved:
		std::cout << "Unit removed\n";
		break;
	default:
		break;
	}

	fld.removeUnit(p);
}

void Dialog::moveFieldUnit()
{
	Point from;
	Point to;

	std::cout << "Enter coordinates from: ";
	std::cin >> from.x >> from.y;
	std::cout << "\n";

	addAndRemoveResult res = removeTail->check(fld, from.x, from.y);

	switch (res)
	{
	case addAndRemoveResult::removeErrorIncorrectCoord:
		std::cout << "Uncorrect coordinates\n";
		return;
	case addAndRemoveResult::removeErrorNoUnit:
		std::cout << "Here is no unit\n";
		return;
	case addAndRemoveResult::unitRemoved:
		std::cout << "Coordinates from correct\n";
		break;
	default:
		break;
	}

	std::cout << "Enter coordinates to: ";
	std::cin >> to.x >> to.y;
	std::cout << "\n";

	bool f = addBase(to);
	if (f == false)
		return;

	fld.moveUnit(from, to);
	std::cout << "Move complete\n";
}

void Dialog::characteristicFieldUnit()
{
	Point p;
	std::cout << "Enter unit coordinates: ";
	std::cin >> p.x >> p.y;
	std::cout << "\n";

	addAndRemoveResult res = removeTail->check(fld, p.x, p.y);

	switch (res)
	{
	case addAndRemoveResult::removeErrorIncorrectCoord:
		std::cout << "Uncorrect coordinates\n";
		return;
	case addAndRemoveResult::removeErrorNoUnit:
		std::cout << "Here is no unit\n";
		return;
	case addAndRemoveResult::unitRemoved:
		std::cout << "Coordinates correct\n";
		break;
	default:
		break;
	}

	fld.getUnitInfo(p);
}

void Dialog::createBaseUnit()
{
	Point p;

	std::cout << "\nEnter coordinates: ";
	std::cin >> p.x >> p.y;
	std::cout << "\n";

	bool f = addBase(p);
	if (f == false)
		return;

	writeUnitsLegend();

	char type = 0;
	std::cout << "Enter unit type(1 symbol): ";
	std::cin >> type;
	std::cout << "\n";

	std::shared_ptr<UnitFactory> unf3 = std::make_shared<Tier3Factory>();
	std::shared_ptr<UnitFactory> unf2 = std::make_shared<Tier2Factory>();
	std::shared_ptr<UnitFactory> unf1 = std::make_shared<Tier1Factory>();
	std::shared_ptr<UnitBase> unit;

	switch (type)
	{
	case 'S':
		unit = unf3->createType1();
		break;
	case 'W':
		unit = unf3->createType2();
		break;
	case 'M':
		unit = unf1->createType1();
		break;
	case 'X':
		unit = unf1->createType2();
		break;
	case 'A':
		unit = unf2->createType1();
		break;
	case 'R':
		unit = unf2->createType2();
		break;
	default:
		std::cout << "Incorrect type\n";
		return;
	}

	if (fld.getBaseMaxUnitsCnt() == 0)
	{
		std::cout << "Can't add more in base\n";
		return;
	}

	fld.createInBase(unit, p);
	std::cout << "Unit added\n";
}

void Dialog::setMaxUnitsCntToBase()
{
	int n = 0;

	std::cout << "Enter count: ";
	std::cin >> n;
	std::cout << "\n";

	BaseMUCResult res = mucTail->check(fld, n);

	switch (res)
	{
	case BaseMUCResult::incorrectData:
		std::cout << "Uncorrect data\n";
		return;
	case BaseMUCResult::alreadyBigger:
		std::cout << "Base already have more units\n";
		return;
	case BaseMUCResult::correct:
		std::cout << "Data correct\n";
		break;
	default:
		break;
	}
	
	fld.setMaxUnitCntToBase(n);
	std::cout << "Data set\n";
}


void Dialog::writeUnitsLegend()
{
	std::cout << "Units legend:\n";
	auto d = fld.getD();

	for (auto& i : d)
		std::cout << i.first << " - " << i.second << "\n";
}

bool Dialog::addBase(Point p)
{
	addAndRemoveResult checkRes = addTail->check(fld, p.x, p.y);
	switch (checkRes)
	{
	case addAndRemoveResult::addErrorIncorrectCoord:
		std::cout << "Uncorrect coordinates\n";
		return false;
	case addAndRemoveResult::addErrorColission:
		std::cout << "Collision\n";
		return false;
	case addAndRemoveResult::unitAdded:
		std::cout << "Corrdinates correct\n";
		break;
	default:
		break;
	}

	return true;
}

void Dialog::speakAboutBase()
{
	for (auto& str : baseCommands)
		std::cout << str << '\n';

	int choise = 5;
	std::cout << "\n" << "Enter command number: ";
	std::cin >> choise;

	switch (choise)
	{
	case 1:
		createBaseUnit();
		break;
	case 2:
		fld.useBase();
		break;
	case 3:
		setMaxUnitsCntToBase();
	default:
		break;
	}
}

void Dialog::showField()
{
	std::cout << fld;
}
