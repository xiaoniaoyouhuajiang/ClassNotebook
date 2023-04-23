#include "Dialog.h"

Dialog::Dialog()
{
	d['S'] = "Scout";
	d['A'] = "Archer";
	d['R'] = "Spearman";
	d['W'] = "Warrior";
	d['X'] = "Assasin";
	d['M'] = "Mage";

	startCommands.push_back("1) Work with base");
	startCommands.push_back("2) Work with units");
	startCommands.push_back("3) Show field");
	startCommands.push_back("4) Write log");
	startCommands.push_back("5) Save state");
	startCommands.push_back("6) Load state");
	startCommands.push_back("7) Quit");

	unitCommands.push_back("1) Move unit");
	unitCommands.push_back("2) Unit characteristic");
	unitCommands.push_back("3) Attack other unit");
	unitCommands.push_back("4) Chill (can't chill on swamp)");

	baseCommands.push_back("1) Create unit");
	baseCommands.push_back("2) Use base-boost");
	baseCommands.push_back("3) Base info");

	logCommands.push_back("1) File log");
	logCommands.push_back("2) Terminal log");
	logCommands.push_back("3) No log");

	files.push_back({ "save1.txt", false });
	files.push_back({ "save2.txt", false });
	files.push_back({ "save3.txt", false });
	
	Field fld2(20, 20);
	fld = fld2;
	
	addTail = std::make_shared<AddCoordCheck>();
	removeTail = std::make_shared<RemoveCoordCheck>();
	mucTail = std::make_shared<PositivelyCheck>();

	addCommand = std::make_shared<AddingCommand>();
	moveCommand = std::make_shared<MovingCommand>();
	attackCommand = std::make_shared<AttackicngCommand>();
	notifyCommand = std::make_shared<NotifyCommand>();
}

void Dialog::speak()
{
	std::cout << "Field size - 20x20\n\n";

	for (auto& str : logCommands)
		std::cout << str << "\n";

	int n;
	std::cout << "Choose log format: ";
	std::cin >> n;
	std::cout << "\n";

	LogTypes type;
	switch (n)
	{
	case 1:
		logOut = std::make_shared<std::ofstream>("log.txt");
		type = LogTypes::File;
		break;
	case 2:
		logOut.reset(&std::cout);
		type = LogTypes::Terminal;
		break;
	default:
		logOut = nullptr;
		std::cout << "OK! No log\n\n";
		type = LogTypes::No;
		break;
	}

	addCommand->setLogProxy(&log);
	moveCommand->setLogProxy(&log);
	attackCommand->setLogProxy(&log);
	notifyCommand->setLogProxy(&log);

	addCommand->setLogType(type);
	moveCommand->setLogType(type);
	attackCommand->setLogType(type);
	notifyCommand->setLogType(type);


	while (true)
	{
		for (auto& str : startCommands)
			std::cout << str << '\n';

		int choise = 7;
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
			(*logOut) << log;
			break;
		case 5:
			speakAboutSave();
			break;
		case 6:
			speakAboutLoad();
			break;
		case 7:
			return;
		default:
			break;
		}

		std::cout << "\n\n";
	}
	
}

void Dialog::speakAboutBase()
{
	for (auto& str : baseCommands)
		std::cout << str << '\n';

	int choise = 4;
	std::cout << "\n" << "Enter command number: ";
	std::cin >> choise;

	switch (choise)
	{
	case 1:
		createUnit();
		break;
	case 2:
		base.notify();
		notifyCommand->execute();
		break;
	case 3:
		base.tellAboutSubscribers();
	default:
		break;
	}
}

void Dialog::speakAboutUnits()
{
	for (auto& str : unitCommands)
		std::cout << str << '\n';

	int choise = 4;
	std::cout << "\n" << "Enter command number: ";
	std::cin >> choise;

	switch (choise)
	{
	case 1:
		moveUnit();
		break;
	case 2:
		tellUnitCharacteristics();
		break;
	case 3:
		unitWantToAttack();
		break;
	case 4:
		unitChill();
	default:
		break;
	}

}

void Dialog::createUnit()
{
	Point p;

	std::cout << "\nEnter coordinates: ";
	std::cin >> p.x >> p.y;
	std::cout << "\n";

	addAndRemoveResult checkRes = addTail->check(fld, p.x, p.y);
	switch (checkRes)
	{
	case addAndRemoveResult::addErrorIncorrectCoord:
		std::cout << "Uncorrect coordinates\n";
		return;
	case addAndRemoveResult::addErrorColission:
		std::cout << "Collision\n";
		return;
	default:
		break;
	}

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

	unit->setPoint(p);
	fld.addUnit(unit, p);
	base.subscribe(unit);
	
	addCommand->setParams(d[unit->name], p);
	addCommand->execute();

	std::cout << "Unit added\n";
}

void Dialog::moveUnit()
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
	default:
		break;
	}

	std::cout << "Enter coordinates to: ";
	std::cin >> to.x >> to.y;
	std::cout << "\n";

	addAndRemoveResult res2 = addTail->check(fld, to.x, to.y);

	switch (res2)
	{
	case addAndRemoveResult::addErrorIncorrectCoord:
		std::cout << "Uncorrect coordinates\n";
		return;
	case addAndRemoveResult::addErrorColission:
		std::cout << "Collision\n";
		return;
	default:
		break;
	}

	fld.moveUnit(from, to);

	moveCommand->setParams(d[fld[to.x][to.y].unit->name], from, to);
	moveCommand->execute();

	std::cout << "Move complete\n";
}

void Dialog::unitWantToAttack()
{
	Point p;

	std::cout << "Enter attacking unit coordinates: ";
	std::cin >> p.x >> p.y;
	std::cout << "\n";

	auto res = removeTail->check(fld, p.x, p.y);

	switch (res)
	{
	case addAndRemoveResult::removeErrorIncorrectCoord:
		std::cout << "Uncorrect coordinates\n";
		return;
	case addAndRemoveResult::removeErrorNoUnit:
		std::cout << "Here is no unit\n";
		return;
	default:
		break;
	}

	size_t unitRange = fld[p.x][p.y].unit->range;
	std::vector<std::shared_ptr<UnitBase>> availableUnits;

	for (int i = p.x - unitRange; i <= p.x + unitRange; ++i)
		for (int j = p.y - unitRange; j <= p.y + unitRange; ++j)
		{
			if (i < 0 || j <  0 || i > fld.getWidth() || j > fld.getHeight() || (i == p.x && j == p.y))
				continue;

			std::shared_ptr<UnitBase> cur = fld[i][j].unit;

			if (cur != nullptr)
				availableUnits.push_back(cur);
		}

	if (availableUnits.empty())
	{
		std::cout << "\nNo units in range\n";
		return;
	}

	std::cout << "\nList of units available for attack:\n\n";

	size_t ind = 1;
	for (auto& unit : availableUnits)
	{
		std::cout << ind << ") ";
		unit->tellAboutMe();
		std::cout << "\n";
		++ind;
	}

	int attackInd = -1;

	std::cout << "Enter attack unit number:\n";
	std::cin >> attackInd;
	std::cout << "\n";

	if (attackInd <= 0 || attackInd > availableUnits.size())
	{
		std::cout << "Uncorrect number\n";
		return;
	}

	auto attack_res = availableUnits[attackInd - 1]->takeDamage(fld[p.x][p.y].unit->damage.get());
	switch (attack_res)
	{
	case takeDamageResult::death:
		fld.removeUnit(availableUnits[attackInd - 1]->p);
		base.unsubscribe(availableUnits[attackInd - 1]);
		std::cout << "Attacked unit dead\n";
		break;
	case takeDamageResult::block:
		std::cout << "Damage blocked\n";
		break;
	case takeDamageResult::dodge:
		std::cout << "Dodge!\n";
		break;
	case takeDamageResult::damageTaken:
		std::cout << "Sucñess!\n";
		break;
	default:
		break;
	}

	attackCommand->setParams(d[fld[p.x][p.y].unit->name], d[availableUnits[attackInd - 1]->name], 
		                     fld[p.x][p.y].unit->damage.get(), attack_res);
	attackCommand->execute();
}

void Dialog::unitChill()
{
	Point p;

	std::cout << "Enter units coordinates: ";
	std::cin >> p.x >> p.y;
	std::cout << "\n";
	
	if (fld[p.x][p.y].type == LandscapeTypes::swamp)
	{
		std::cout << "Swamp!\n";
		return;
	}

	auto res = removeTail->check(fld, p.x, p.y);

	switch (res)
	{
	case addAndRemoveResult::removeErrorIncorrectCoord:
		std::cout << "Uncorrect coordinates\n";
		return;
	case addAndRemoveResult::removeErrorNoUnit:
		std::cout << "Here is no unit\n";
		return;
	default:
		break;
	}

	fld[p.x][p.y].unit->hp.increase(20);
}

void Dialog::showField()
{
	std::cout << fld;
}

void Dialog::speakAboutSave()
{
	std::cout << "Info about save files:\n\n";

	size_t ind = 1;
	for (auto& i : files)
	{
		std::cout << ind << ") " << i.name << " - " << (i.is_used ? "already used" : "empty") << "\n";
		++ind;
	}

	int n;
	std::cout << "Enter number of chosen save-file (another number to cancel operation): ";
	std::cin >> n;
	std::cout << "\n";

	--n;
	if (n < 0 || n >= files.size())
		return;

	if (files[n].is_used == true)
	{
		char c;
		std::cout << "Are you sure? (Y\N)\n";
		std::cin >> c;
		std::cout << "\n";
		if (c != 'Y')
			return;
	}

	auto snap = fld.save();
	bool res = snap->write(files[n].name);

	if (res == false)
		std::cout << files[n].name << " " << "is not available\n";
	else
	{
		std::cout << "State saved\n";
		files[n].is_used = true;
	}
}

void Dialog::speakAboutLoad()
{
	std::cout << "Info about load files:\n\n";

	size_t ind = 1;
	for (auto& i : files)
	{
		std::cout << ind << ") " << i.name << " - " << (i.is_used ? "full" : "empty") << "\n";
		++ind;
	}

	int n;
	std::cout << "Enter number of chosen load-file (another number to cancel operation): ";
	std::cin >> n;
	std::cout << "\n";

	--n;
	if (n < 0 || n >= files.size())
		return;

	std::shared_ptr<Snapshot> snap = std::make_shared<SnapReader>();
	bool res = snap->read(files[n].name);
	if (res == false)
	{
		std::cout << "File is broken!\n";
		return;
	}

	bool loadRes = fld.load(snap);
	if (loadRes == false)
	{
		std::cout << "File data is broken\n";
		return;
	}
	std::cout << "Loading complete\n";
}

void Dialog::writeUnitsLegend()
{
	std::cout << "\nUnits legend:\n";
	for (auto& i : d)
		std::cout << i.first << " - " << i.second << "\n";
	std::cout << "\n";
}

void Dialog::tellUnitCharacteristics()
{
	Point p;

	std::cout << "Enter unit coordinates: ";
	std::cin >> p.x >> p.y;
	std::cout << "\n";

	auto res = removeTail->check(fld, p.x, p.y);

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

	fld[p.x][p.y].unit->tellAboutMe();

}
