#include "Field.h"

Field::Field()
{
	d['S'] = "Scout";
	d['W'] = "Warrior";
	d['M'] = "Mage";
	d['X'] = "Assasin";
	d['A'] = "Archer";
	d['R'] = "Rogue";
}

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
	std::swap(base, other.base);
}

Field::Field(Field const& other)
{
	fld = other.fld;
	width = other.width;
	height = other.height;
	base = other.base;
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

Field::Field(Field&& other)
{
	swap(other);
	deleteData(other);
}

addAndRemoveResult Field::addUnit(Field::UnitPtr unitToAdd, Point p)
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
		return addAndRemoveResult::unitAdded;

	switch (effect.what)
	{
	case EffectTypes::damage:
		fld[p.x][p.y].unit->damage.increase(effect.how_much);
		break;
	case EffectTypes::range:
		fld[p.x][p.y].unit->range += effect.how_much;
		break;
	case EffectTypes::hp:
		fld[p.x][p.y].unit ->hp.increase(effect.how_much);
		break;
	}
	fld[p.x][p.y].effect = effect;

	return addAndRemoveResult::unitAdded;
}


addAndRemoveResult Field::removeUnit(Point p)
{
	if (fld[p.x][p.y].unit->from_base == true)
		base.forgetAbout(p);

	fld[p.x][p.y].unit = nullptr;
	fld[p.x][p.y].name[2] = ' ';
	fld[p.x][p.y].effect = { 0, EffectTypes::damage };

	return addAndRemoveResult::unitRemoved;
}

addAndRemoveResult Field::createInBase(Field::UnitPtr unitToAdd, Point p)
{
	base.addUnit(p);
	unitToAdd->from_base = true;
	return addUnit(unitToAdd, p);
}

moveResult Field::moveUnit(Point from, Point to)
{

	UnitPtr unitFrom = fld[from.x][from.y].unit;
	auto prev_effect = fld[from.x][from.y].effect;

	auto removeRes = removeUnit(from);

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
	if (fld[from.x][from.y].unit->from_base == true)
		base.update(from, to);

	auto addRes = addUnit(unitFrom, to);

	return moveResult::moveComplete;

}

void Field::getUnitInfo(Point p)
{
	std::cout << "Info about unit:\n";
	std::cout << "Unit type - " << d[fld[p.x][p.y].unit->name] << "\n";
	std::cout << "Unit hp - " << fld[p.x][p.y].unit->hp.get() << "\n";
	std::cout << "Unit damage - " << (fld[p.x][p.y].unit->damage.get() < 0 ? 0 : fld[p.x][p.y].unit->damage.get()) << "\n";
	std::cout << "Unit range - " << fld[p.x][p.y].unit->range << "\n";
}

void Field::deleteData(Field& f) const
{
	f.fld = nullptr;
	f.width = 0;
	f.height = 0;
}

void Field::useBase()
{
	for (auto& p : base.notify())
	{
		fld[p.x][p.y].unit->damage.increase(20);
	}
}

void Field::setMaxUnitCntToBase(size_t cnt)
{
	base.setUnitsCnt(cnt);
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

std::map<char, std::string> Field::getD() const
{
	return d;
}

size_t Field::getBaseMaxUnitsCnt() const
{
	return base.getMaxUnitsCnt();
}

size_t Field::getBaseUnitsCnt() const
{
	return base.getNowUnitsCnt();
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