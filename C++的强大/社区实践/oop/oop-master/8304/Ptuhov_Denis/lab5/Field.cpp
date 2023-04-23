#include "Field.h"
#include "UnitFactory.h"

Field::Field(size_t new_width, size_t new_height) : width(new_width), height(new_height)
{
	FldType new_fld(new std::shared_ptr<fieldElement[]>[height], std::default_delete<std::shared_ptr<fieldElement[]>[]>());
	for (size_t i = 0; i < height; ++i)
	{
		std::shared_ptr<fieldElement[]> new_elem(new fieldElement[width], std::default_delete<fieldElement[]>());
		new_fld[i] = new_elem;
	}

	fld = new_fld;

	for (size_t i = 0; i < height; ++i)
		for (size_t j = 0; j < width; ++j)
		{
			if (j < 3 && i < 3)
				continue;

			fld[i][j].name = { ' ', ' ' , ' ' };
			size_t chance = std::rand() % 3;
			LandscapeTypes type;
			char name;
			switch (chance)
			{
			case 0:
				type = LandscapeTypes::ground;
				name = 'G';
				break;
			case 1:
				type = LandscapeTypes::mountain;
				name = 'M';
				break;
			case 2:
				type = LandscapeTypes::swamp;
				name = 'S';
				break;
			}

			fld[i][j].name[0] = name;
			fld[i][j].type = type;
			
			std::shared_ptr<NtrlObjNameExpansion> ntrl;
			size_t chanceNtrl = std::rand() % 10;
			switch (chanceNtrl)
			{
			case 1:
				ntrl = std::make_shared<HillingWaterFall>();
				break;
			case 2:
				ntrl = std::make_shared<Trap>();
				break;
			case 3:
				ntrl = std::make_shared<PowerStatue>();
				break;
			case 4:
				ntrl = std::make_shared<InsightStatue>();
				break;
			default:
				break;
			}

			fld[i][j].ntrl = ntrl;
			fld[i][j].name[1] = '?';
		}
}

void Field::swap(Field& other)
{
	std::swap(width, other.width);
	std::swap(height, other.height);
	std::swap(fld, other.fld);
}

Field::Field(Field const& other)
{
	fld = other.fld;
	width = other.width;
	height = other.height;
}

Field& Field::operator=(Field const& other)
{
	if (&other != this)
	{
		Field(other).swap(*this);
	}
	return *this;
}

Field& Field::operator=(Field&& other)
{
	swap(other);
	deleteData(other);
	return *this;
}

std::shared_ptr<Field::fieldElement[]>& Field::operator[](size_t i)
{
	return fld[i];
}

std::shared_ptr<Field::fieldElement[] > Field::operator[](size_t i) const
{
	return fld[i];
}

std::shared_ptr<Snapshot> Field::save()
{
	std::string fieldData;

	for (size_t i = 0; i < height; ++i)
		for (size_t j = 0; j < width; ++j)
		{
			if (j <3 && i < 3)
				fieldData += 'B';
			else
				fieldData += fld[i][j].name[0];
		}
	fieldData += '.';

	for (size_t i = 0; i < height; ++i)
		for (size_t j = 0; j < width; ++j)
		{
			if (j < 3 && i < 3)
				fieldData += 'B';
			else
			{
				if (fld[i][j].ntrl != nullptr)
					fieldData += fld[i][j].ntrl->getName();
				else
					fieldData += '?';
			}
		}
	fieldData += '.';

	for (size_t i = 0; i < height; ++i)
		for (size_t j = 0; j < width; ++j)
		{
			if (j < 3 && i < 3)
				continue;
			else
			{
				if (fld[i][j].unit != nullptr)
				{
					auto prev_effect = fld[i][j].effect;

					switch (prev_effect.what)
					{
					case EffectTypes::damage:
						fld[i][j].unit->damage.decrease(prev_effect.how_much);
						break;
					case EffectTypes::range:
						fld[i][j].unit->range -= prev_effect.how_much;
						break;
					case EffectTypes::hp:
						fld[i][j].unit->hp.decrease(prev_effect.how_much);
						break;
					}

					fieldData += fld[i][j].unit->name;
					fieldData += ';';
					fieldData += std::to_string(fld[i][j].unit->p.x);
					fieldData += ';';
					fieldData += std::to_string(fld[i][j].unit->p.y);
					fieldData += ';';
					fieldData += std::to_string(fld[i][j].unit->damage.get());
					fieldData += ';';
					fieldData += std::to_string(fld[i][j].unit->hp.get());
					fieldData += ';';
					fieldData += std::to_string(fld[i][j].unit->range);
					fieldData += ';';

					switch (prev_effect.what)
					{
					case EffectTypes::damage:
						fld[i][j].unit->damage.increase(prev_effect.how_much);
						break;
					case EffectTypes::range:
						fld[i][j].unit->range += prev_effect.how_much;
						break;
					case EffectTypes::hp:
						fld[i][j].unit->hp.increase(prev_effect.how_much);
						break;
					}
				}
			}
		}

	return std::make_shared<Snapshot>(fieldData);
}

bool Field::load(std::shared_ptr<Snapshot> snap)
{
	std::string snapData = snap->get();

	Field tmp(20, 20);
	size_t ind = 0;

	for (size_t i = 0; i < 20; ++i)
		for (size_t j = 0; j < 20; ++j)
		{
			if (ind == snapData.size())
				return false;

			if (j < 3 && i < 3)
			{
				if (snapData[ind] != 'B')
					return false;
			}
			else
			{
				switch (snapData[ind])
				{
				case 'G':
					tmp.fld[i][j].type = LandscapeTypes::ground;
					tmp.fld[i][j].name[0] = 'G';
					break;
				case 'M':
					tmp.fld[i][j].type = LandscapeTypes::mountain;
					tmp.fld[i][j].name[0] = 'M';
					break;
				case 'S':
					tmp.fld[i][j].type = LandscapeTypes::swamp;
					tmp.fld[i][j].name[0] = 'M';
					break;
				default:
					return false;
				}
			}

			++ind;
		}

	if (snapData[ind] != '.')
		return false;
	++ind;


	std::shared_ptr<NtrlObjNameExpansion> ntrl;
	for (size_t i = 0; i < 20; ++i)
		for (size_t j = 0; j < 20; ++j)
		{
			if (ind == snapData.size())
				return false;

			switch (snapData[ind])
			{
			case 'W':
				ntrl = std::make_shared<HillingWaterFall>();
				break;
			case 'T':
				ntrl = std::make_shared<Trap>();
				break;
			case 'P':
				ntrl = std::make_shared<PowerStatue>();
				break;
			case 'I':
				ntrl = std::make_shared<InsightStatue>();
				break;
			case 'B':
				break;
			case '?':
				ntrl = nullptr;
				break;
			default:
				return false;
			}

			tmp.fld[i][j].ntrl = ntrl;

			++ind;
		}

	if (snapData[ind] != '.')
		return false;
	++ind;
	
	std::shared_ptr<UnitBase> unit;
	std::regex pattern("([SWMXAR]);(\\d+);(\\d+);(\\d+);(\\d+);(\\d+);");
	std::smatch match;
	std::string unitInfo(snapData.begin() + ind, snapData.end());

	std::shared_ptr<UnitFactory> unf3 = std::make_shared<Tier3Factory>();
	std::shared_ptr<UnitFactory> unf2 = std::make_shared<Tier2Factory>();
	std::shared_ptr<UnitFactory> unf1 = std::make_shared<Tier1Factory>();

	while (std::regex_search(unitInfo, match, pattern) != 0)
	{
		char name = match[1].str()[0];
		switch (name)
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
			return false;
		}

		Point p = { std::stoi(match[2].str()), std::stoi(match[3].str()) };
		if (p.x < 3 && p.y < 3 || tmp.fld[p.x][p.y].unit != nullptr)
			return false;

		unit->damage.get() = std::stoi(match[4].str());
		unit->hp.get() = std::stoi(match[5].str());
		unit->range = std::stoi(match[6].str());
		unit->setPoint(p);
		tmp.addUnit(unit, p);


		unitInfo.erase(unitInfo.begin() + match.position(), unitInfo.begin() + match.position() + match.length());
	}

	if (unitInfo.size() != 0)
		return false;

	(*this) = tmp;

	return true;
}

void Field::addUnit(std::shared_ptr<UnitBase> unitToAdd, Point p)
{
	if (fld[p.x][p.y].ntrl != nullptr)
	{
		(*unitToAdd)(fld[p.x][p.y].ntrl);
		fld[p.x][p.y].name[1] = fld[p.x][p.y].ntrl->getName();
	}
	else
		fld[p.x][p.y].name[1] = ' ';


	fld[p.x][p.y].unit = unitToAdd;
	fld[p.x][p.y].name[2] = unitToAdd->name;

	LandscapeProxy proxy;
	auto effect = proxy.get(fld[p.x][p.y].type, unitToAdd->name);
	if (effect.how_much == 0)
		return;

	(*unitToAdd)(effect);
	fld[p.x][p.y].effect = effect;
}

Field::Field(Field&& other)
{
	swap(other);
	deleteData(other);
}

addAndRemoveResult Field::removeUnit(Point p)
{
	fld[p.x][p.y].unit = nullptr;
	fld[p.x][p.y].name[2] = ' ';
	fld[p.x][p.y].effect = { 0, EffectTypes::damage };

	return addAndRemoveResult::unitRemoved;
}

moveResult Field::moveUnit(Point from, Point to)
{
	UnitPtr unitFrom = fld[from.x][from.y].unit;
	auto prev_effect = fld[from.x][from.y].effect;

	removeUnit(from);

	switch (prev_effect.what)
	{
	case EffectTypes::damage:
		unitFrom->damage.decrease(prev_effect.how_much);
		break;
	case EffectTypes::range:
		unitFrom->range -= prev_effect.how_much;
		break;
	case EffectTypes::hp:
		unitFrom->hp.decrease(prev_effect.how_much);
		break;
	}

	addUnit(unitFrom, to);
	unitFrom->setPoint(to);

	return moveResult::moveComplete;

}

void Field::deleteData(Field& f) const
{
	f.fld = nullptr;
	f.width = 0;
	f.height = 0;
}

bool Field::empty() const
{
	return height == 0 && width == 0;
}

size_t Field::getHeight() const
{
	return height;
}

size_t Field::getWidth() const
{
	return width;
}

void operator<<(std::ostream& out, Field& f)
{
	if (f.fld == nullptr)
	{
		std::cout << "\nEmpty field\n\n";
		return;
	}

	std::cout << std::string(7, ' ');
	for (size_t j = 0; j < f.width; ++j)
	{
		std::cout << j << std::string(7, ' ');
	}
	std::cout << "\n";

	std::cout << std::string(5, ' ');
	std::cout << "\n";

	for (size_t i = 0; i < f.height; ++i)
	{
		std::cout << i << std::string(3 - std::to_string(i).size(), ' ');
		for (size_t j = 0; j < f.width; ++j)
		{
			std::cout << "| ";

			if (j < 3 && i < 3)
			{
				std::cout << "  " << 'B' << std::string(std::to_string(j).size(), ' ') << "  ";
				continue;
			}

			std::cout << f[i][j].name[0] << "/" << f[i][j].name[1] << "/" << f[i][j].name[2] << std::string(std::to_string(j).size(), ' ');
		}
		std::cout << '|' << "\n";
		std::cout << std::string(5, ' ');
		std::cout << "\n";
	}
}

Field::iterator::iterator(FldType& fld, size_t width, size_t height, char c) : fldPtr(&fld), width(width), height(height)
{
	if (c == 'e')
	{
		strNumber = width;
		strIndex = 0;
	}
}

Field::iterator& Field::iterator::operator++()
{
	++strIndex;
	if (strIndex == height)
	{
		++strNumber;
		strIndex = 0;
	}

	return *this;
}

Field::iterator Field::iterator::operator++(int)
{
	iterator tmp(*this);
	++(*this);
	return tmp;
}

Field::iterator& Field::iterator::operator--()
{
	if (strIndex == 0)
	{
		--strNumber;
		strIndex = 0;
	}
	else
		--strIndex;

	return *this;
}

Field::iterator Field::iterator::operator--(int)
{
	iterator tmp(*this);
	--(*this);
	return tmp;
}

Field::fieldElement& Field::iterator::operator*()
{
	return (*fldPtr)[strNumber][strIndex];
}

Field::fieldElement* Field::iterator::operator->()
{
	return &(*fldPtr)[strNumber][strIndex];
}

bool Field::iterator::operator!=(iterator const& it) const
{
	return !(it.strIndex == strIndex && it.strNumber == strNumber);
}