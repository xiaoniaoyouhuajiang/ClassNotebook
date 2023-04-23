#include "Dialog.h"

void Dialog::start()
{
	std::cout << greeting;
	speak();
}

void Dialog::speak()
{
	while (true)
	{
		std::cout << chooseOption;
		for (auto& opt : options)
			std::cout << opt;
		std::cout << choiseRequest;
		int choise = 6;
		std::cin >> choise;
		switch (choise)
		{
		case 1:
			createFieldChoise();
			break;
		case 2:
			addUnitChoise();
			break;
		case 3:
			removeUnitChoise();
			break;
		case 4:
			std::cout << fld;
			break;
		case 5:
			moveChoise();
			break;
		case 6:
			maxUnitsCntChoise();
			break;
		case 7:
			return;

		default:
			std::cout << "Try again\n\n";
			break;
		}
	}
}

void Dialog::createFieldChoise()
{
	int width = 0;
	int length = 0;
	std::cout << "Set width and length: ";
	std::cin >> width;
	std::cin >> length;

	if (width <= 0 || length <= 0 || width >= 100 || length >= 100)
	{
		std::cout << "Incorrect args\n\n";
		return;
	}

	Field new_fld(width, length);
	fld = new_fld;

	std::cout << "\nField created\n\n";
}

void Dialog::addUnitChoise()
{
	if (fld.empty() || fld.getMaxUnitsCnt() == -1)
	{
		std::cout << "\nField is empty or max units cnt doesn't set!\n\n";
		return;
	}

	Point p;
	std::cout << "Write coordinates (write -1 to see map): ";
	std::cin >> p.x;
	if (p.x == -1)
	{
		std::cout << "\n";
		std::cout << fld;
		addUnitChoise();
		return;
	}

	std::cin >> p.y;
	readUnitType(p);
}

void Dialog::removeUnitChoise()
{
	if (fld.empty() || fld.getMaxUnitsCnt() == -1)
	{
		std::cout << "\nField is empty or max units cnt doesn't set!\n\n";
		return;
	}

	Point p;
	std::cout << "Write coordinates: ";
	std::cin >> p.x;

	std::cin >> p.y;

	auto removeRes = fld.removeUnit(p);
	if (removeRes == addAndRemoveResult::removeErrorNoUnit)
	{
		std::cout << "\nError. No unit\n\n";
		return;
	}
	if (removeRes == addAndRemoveResult::removeErrorIncorrectCoord)
	{
		std::cout << "\nIncorrect coordinates\n\n";
		return;
	}

	std::cout << "\nUnit removed correctly\n\n";

}

void Dialog::moveChoise()
{
	if (fld.empty() || fld.getMaxUnitsCnt() == -1)
	{
		std::cout << "\nField is empty or max units cnt doesn't set!\n\n";
		return;
	}

	std::cout << "Coordinates from: ";
	Point p1;
	std::cin >> p1.x >> p1.y;

	std::cout << "\nPoints from: ";
	Point p2;
	std::cin >> p2.x >> p2.y;

	auto res = fld.moveUnit(p1, p2);
	if (res == moveResult::moveCoordinateError)
	{
		std::cout << "Incorrect data\n";
		return;
	}

	std::cout << "\nMove complete\n\n";
}

void Dialog::maxUnitsCntChoise()
{
	if (fld.getMaxUnitsCnt() != -1)
	{
		std::cout << "Max unit cnt already set\n\n";
		return;
	}
	int a;

	std::cout << "Enter: ";
	std::cin >> a;

	auto res = fld.setMaxUnitsCnt(a);
	if (res == maxUnitsCntResult::incorrectData)
	{
		std::cout << "Incorrect data\n\n";
		return;
	}

	std::cout << "\nData set correctly\n\n";
}

void Dialog::writeUnitsLegend()
{
	for (auto& unit : unitsLegend)
	{
		std::cout << unit.first << " - " << unit.second << "\n";
	}
}

void Dialog::readUnitType(Point p)
{
	std::cout << "\nWrite units type (write h to see units legend): ";
	char c;
	std::cin >> c;
	std::cout << "\n";
	if (c == 'h')
	{
		writeUnitsLegend();
		readUnitType(p);
		return;
	}

	std::shared_ptr<UnitBase> unitToAdd = nullptr;
	/*switch (c)
	{
	case 'A':
		unitToAdd = static_cast<UnitBase*>(new Archer());
		break;
	case 'R':
		unitToAdd = static_cast<UnitBase*>(new Rogue());
		break;
	case 'M':
		unitToAdd = static_cast<UnitBase*>(new Mage());
		break;
	case 'E':
		unitToAdd = static_cast<UnitBase*>(new Spearman());
		break;
	case 'N':
		unitToAdd = static_cast<UnitBase*>(new Shielder());
		break;
	case 'S':
		unitToAdd = static_cast<UnitBase*>(new Assasin());
		break;
	default:
		std::cout << "Incorrect type. Try again\n";
		readUnitType(p);
		return;
	}*/

	auto res = fld.addUnit(unitToAdd, p);
	if (res == addAndRemoveResult::addErrorColission)
	{
		std::cout << "Collision! Unit already exist\n\n";
		return;
	}
	if (res == addAndRemoveResult::addErrorIncorrectCoord)
	{
		std::cout << "Incorrect Coordinates\n\n";
		return;
	}
	if (res == addAndRemoveResult::MaxUnitsCntError)
	{
		std::cout << "Units cnt are already max\n\n";
		return;
	}

	std::cout << "Unit added\n\n";
}
