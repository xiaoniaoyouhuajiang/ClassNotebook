#include "Dialog.h"

Dialog::Dialog()
{
	d['S'] = "Scout";
	d['A'] = "Archer";
	d['R'] = "Spearman";
	d['W'] = "Warrior";
	d['X'] = "Assasin";
	d['M'] = "Mage";

	startCommands.push_back("1) Start new game");
	startCommands.push_back("8) Quit");

	unitCommands.push_back("1) Move unit");
	unitCommands.push_back("2) Attack other unit");
	unitCommands.push_back("3) Chill (can't chill on swamp)");

	baseCommands.push_back("1) Create unit");
	baseCommands.push_back("2) Use base-boost");
	baseCommands.push_back("3) Base info");

//	logCommands.push_back("1) File log");
//	logCommands.push_back("2) Terminal log");
//	logCommands.push_back("3) No log");

	files.push_back({ "save1.txt", false });
	files.push_back({ "save2.txt", false });
	files.push_back({ "save3.txt", false });
	
	ruleCommands.push_back("1) Fast game (2 players)");
	ruleCommands.push_back("2) Standart game (3 players)");
		
	
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
/*	std::cout << "Field size - 20x20\n\n";

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
*/
	int n = 3;
	while (n != 1 && n != 2)
	{
		std::cout << "Choose game format:\n";
		for (auto& str : ruleCommands)
			std::cout << str << '\n';
		std::cin >> n;
		std::cout << "\n\n";
	}

	std::shared_ptr<UnitFactory> fct1 = std::make_shared<Tier1Factory>();
	std::shared_ptr<UnitFactory> fct2 = std::make_shared<Tier2Factory>();
	std::shared_ptr<UnitFactory> fct3 = std::make_shared<Tier3Factory>();

	if (n == 1)
	{
		// подготовка поля и инициализация юнитов
		Field fld(10, 10);

		fld.addUnit(fct2->createType1(), { 3, 3 });
		fld.addUnit(fct1->createType2(), { 3, 2 });
		fld.addUnit(fct3->createType2(), { 2, 3 });

		fld.addUnit(fct2->createType1(), { 9, 9 });
		fld.addUnit(fct1->createType2(), { 9, 8 });
		fld.addUnit(fct3->createType2(), { 8, 9 });

		this->fld = fld;

		std::vector<std::shared_ptr<UnitBase>> firstPlayerUnits = { fld[2][3].unit, fld[3][2].unit, fld[3][3].unit };
		std::vector<std::shared_ptr<UnitBase>> secondPlayerUnits = { fld[8][9].unit, fld[9][8].unit, fld[9][9].unit };

		Game<FastGameRule, 2> game(firstPlayerUnits, secondPlayerUnits);


		int ind;
		while (true)
		{
			auto pts = game.getCurPlayerPts();
			if (pts.destroy_pts == 3)
			{
				std::cout << "Player " << game.getPlayerNumber() << " you win, yout destroy all enemy units\n";
				return;
			}
			if (pts.shtrum_pts == 5)
			{
				std::cout << "Player 2 you win, you shturm base\n";
				return;
			}

			std::cout << "Show field? (Y/N)\n";
			char c;
			std::cin >> c;
			if (c == 'Y')
				std::cout << fld;

			int num = game.getPlayerNumber();
			std::cout << "Player " << num << " it's your turn!\n";

			if (num == 1)
				std::cout << "For destroyings enemy units: " << pts.destroy_pts << " of 3\n";
			else
			{
				std::cout << "For destroyings enemy units: " << pts.destroy_pts << " of 3\n";
				std::cout << "For base shturm: " << pts.shtrum_pts << " of 5\n";
			}
			std::cout << "Choose unit:\n\n";

			auto units = game.getCurPlayerUnits();
			ind = 0;
			for (auto& unit : units)
			{
				std::cout << ++ind << ") " << d[unit->name] << "\n";
				unit->tellAboutMe();
				std::cout << "\n";
			}
			std::cout << ++ind << ") " << "Start new game\n\n";

			int unit_ind;
			std::cin >> unit_ind;
			if (unit_ind == 4)
			{
				speak();
				return;
			}

			if (unit_ind <= 0 || unit_ind > 3)
				continue;
			--unit_ind;

			std::cout << "Chosen unit: ";
			std::cout << d[units[unit_ind]->name] << "\n";
			std::cout << "Choose option for unit:\n";
			for (auto& str : unitCommands)
				std::cout << str << "\n";

			int command_ind;
			std::cin >> command_ind;

			try
			{
				switch (command_ind)
				{
				case 1:
					moveUnit(units[unit_ind]->p);
					break;
				case 2:
					unitWantToAttack(units[unit_ind]->p);
					break;
				case 3:
					units[unit_ind]->hp.increase(20);
					break;
				default:
					throw my_exceptions("Uncorrect uperation number\n");
					break;
				}
			}
			catch (my_exceptions& e)
			{
				std::cout << e.what();
			}

			game.changePlayer();
		}
		
	}
	else
	{
		Field fld(20, 20);
		this->fld = fld;

		fld.addUnit(fct2->createType1(), { 3, 3 });
		fld.addUnit(fct1->createType2(), { 3, 2 });
		fld.addUnit(fct3->createType2(), { 2, 3 });
		fld.addUnit(fct3->createType1(), { 1, 3 });
		fld.addUnit(fct3->createType2(), { 3, 1 });
		fld.addUnit(fct1->createType1(), { 3, 0 });
		fld.addUnit(fct2->createType2(), { 0, 3 });

		fld.addUnit(fct2->createType1(), { 19, 1 });
		fld.addUnit(fct1->createType2(), { 18, 1 });
		fld.addUnit(fct3->createType2(), { 17, 1 });

		fld.addUnit(fct2->createType1(), { 1, 19 });
		fld.addUnit(fct1->createType2(), { 2, 19 });
		fld.addUnit(fct3->createType2(), { 3, 19 });

		std::vector<std::shared_ptr<UnitBase>> firstPlayerUnits = { fld[2][3].unit, fld[3][2].unit, fld[3][3].unit, fld[1][3].unit, fld[3][1].unit, fld[3][0].unit, fld[0][3].unit };
		std::vector<std::shared_ptr<UnitBase>> secondPlayerUnits = { fld[19][1].unit, fld[18][1].unit, fld[17][1].unit};
		std::vector<std::shared_ptr<UnitBase>> thirdPlayerUnits = { fld[1][19].unit, fld[2][19].unit, fld[3][19].unit};

		Game<MediumGameRule, 3> game(firstPlayerUnits, secondPlayerUnits, thirdPlayerUnits);

		int ind;
		while (true)
		{
			int pts = game.getCurPlayerPts();
			int num = game.getPlayerNumber();

			if (pts == 6 && num == 1)
			{
				std::cout << "Player 1 you win, yout destroy all enemy units\n";
				return;
			}
			if (pts == 5 && (num == 2 || num == 3))
			{
				std::cout << "Player " << num << " you win, you shturm base\n";
				return;
			}

			std::cout << "Show field? (Y/N)\n";
			char c;
			std::cin >> c;
			if (c == 'Y')
				std::cout << fld;

			std::cout << "Player " << num << " it's your turn!\n";
			std::cout << "Choose unit:\n\n";

			auto units = game.getCurPlayerUnits();
			ind = 0;
			for (auto& unit : units)
			{
				std::cout << ++ind << ") " << d[unit->name] << "\n";
				unit->tellAboutMe();
				std::cout << "\n";
			}
			std::cout << ++ind << ") " << "Start new game\n\n";

			int unit_ind;
			std::cin >> unit_ind;
			if (unit_ind == ind)
			{
				speak();
				return;
			}

			if (unit_ind <= 0 || unit_ind >= units.size())
				continue;
			--unit_ind;

			std::cout << "Chosen unit: ";
			std::cout << d[units[unit_ind]->name] << "\n";
			std::cout << "Choose option for unit:\n";
			for (auto& str : unitCommands)
				std::cout << str << "\n";

			int command_ind;
			std::cin >> command_ind;

			try
			{
				switch (command_ind)
				{
				case 1:
					moveUnit(units[unit_ind]->p);
					break;
				case 2:
					unitWantToAttack(units[unit_ind]->p);
					break;
				case 3:
					units[unit_ind]->hp.increase(20);
					break;
				default:
					throw my_exceptions("Uncorrect uperation number\n");
					break;
				}
			}
			catch (my_exceptions& e)
			{
				std::cout << e.what();
			}

			game.changePlayer();
		}
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
		moveUnit({0, 0});
		break;
	case 2:
		tellUnitCharacteristics();
		break;
	case 3:
		unitWantToAttack({0, 0});
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

	try
	{
		switch (checkRes)
		{
		case addAndRemoveResult::addErrorIncorrectCoord:
			throw my_exceptions("Uncorrect coordinates\n");
			return;
		case addAndRemoveResult::addErrorColission:
			throw my_exceptions("Collision\n");
			return;
		default:
			break;
		}
	}
	catch (my_exceptions& e)
	{
		std::cout << e.what();
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
		std::cout << "Uncorrect type\n";
		return;
	}

	unit->setPoint(p);
	fld.addUnit(unit, p);
	base.subscribe(unit);
	
	addCommand->setParams(d[unit->name], p);
	addCommand->execute();

	std::cout << "Unit added\n";
}

void Dialog::moveUnit(Point from)
{
	Point to;

	std::cout << "Enter coordinates to: ";
	std::cin >> to.x >> to.y;
	std::cout << "\n";

	addAndRemoveResult res2 = addTail->check(fld, to.x, to.y);

	try
	{
		switch (res2)
		{
		case addAndRemoveResult::addErrorIncorrectCoord:
			throw my_exceptions("Uncorrect coordinates\n");
			return;
		case addAndRemoveResult::addErrorColission:
			throw my_exceptions("Collision\n");
			return;
		default:
			break;
		}
	}
	catch (my_exceptions& e)
	{
		std::cout << e.what();
	}

	int dx = std::abs(from.x - to.x);
	int dy = std::abs(from.y - to.y);

	try
	{
		if (dx + dy > fld[from.x][from.y].unit->range)
		{
			throw  my_exceptions("Out of range\n");
			return;
		}
	}
	catch (my_exceptions& e)
	{
		std::cout << e.what();
	}

	fld.moveUnit(from, to);

//	moveCommand->setParams(d[fld[to.x][to.y].unit->name], from, to);
//	moveCommand->execute();

	std::cout << "Move complete\n";
}

void Dialog::unitWantToAttack(Point p)
{
	size_t unitRange = fld[p.x][p.y].unit->range;
	std::vector<std::shared_ptr<UnitBase>> availableUnits;

	for (int i = p.x - unitRange; i <= p.x + unitRange; ++i)
		for (int j = p.y - unitRange; j <= p.y + unitRange; ++j)
		{
			if (i < 0 || j <  0 || i >= fld.getWidth() || j >= fld.getHeight() || (i == p.x && j == p.y))
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

	try
	{
		if (attackInd <= 0 || attackInd > availableUnits.size())
		{
			throw my_exceptions("Uncorrect number\n");
			return;
		}
	}
	catch (my_exceptions& e)
	{
		std::cout << e.what();
	}

	auto attack_res = availableUnits[attackInd - 1]->takeDamage(fld[p.x][p.y].unit->damage.get());
	switch (attack_res)
	{
	case takeDamageResult::death:
		fld.removeUnit(availableUnits[attackInd - 1]->p);
		std::cout << "Attacked unit dead\n";
		break;
	case takeDamageResult::block:
		std::cout << "Damage blocked\n";
		break;
	case takeDamageResult::dodge:
		std::cout << "Dodge!\n";
		break;
	case takeDamageResult::damageTaken:
		std::cout << "Sucсess!\n";
		break;
	default:
		break;
	}

//	attackCommand->setParams(d[fld[p.x][p.y].unit->name], d[availableUnits[attackInd - 1]->name], 
//		                     fld[p.x][p.y].unit->damage.get(), attack_res);
//	attackCommand->execute();
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

	try
	{
		switch (res)
		{
		case addAndRemoveResult::removeErrorIncorrectCoord:
			throw my_exceptions("Uncorrect coordinates\n");
			return;
		case addAndRemoveResult::removeErrorNoUnit:
			throw my_exceptions("Here is no unit\n");
			return;
		default:
			break;
		}
	}
	catch (my_exceptions& e)
	{
		std::cout << e.what();
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
		std::cout << ind << ") " << i.name << " - " << (i.is_used ? "already used" : "not used") << "\n";
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
		std::cout << "Are you sure? (Y/N)\n";
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
