#include "Field.h"

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

			size_t chance = std::rand() % 3;
			LandscapeTypes type;
			char name;
			switch (chance)
			{
			case 0:
				type = LandscapeTypes::ground;
				name = 'g';
				break;
			case 1:
				type = LandscapeTypes::mountain;
				name = 'm';
				break;
			case 2:
				type = LandscapeTypes::swamp;
				name = 's';
				break;
			}

			fld[i][j].type = type;
			fld[i][j].name = name;
		}

	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 3; ++j)
		{
			fld[i][j].name = 'B';
		}


	fld[4][4].type = LandscapeTypes::mountain;
	fld[5][5].type = LandscapeTypes::swamp;

	fld[6][6].ntrl = std::make_shared<Trap>();
	fld[6][6].type = LandscapeTypes::swamp;
	fld[7][7].ntrl = std::make_shared<HillingWaterFall>();
	fld[7][7].type = LandscapeTypes::mountain;
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

Field::Field(Field&& other)
{
	swap(other);
	deleteData(other);
}

addAndRemoveResult Field::addUnit(Field::UnitPtr unitToAdd, Point p)
{
	if (p.x < 0 || p.y < 0 || p.x >= width || p.y >= height || (p.x < 3 && p.y < 3))
		return addAndRemoveResult::addErrorIncorrectCoord;

	if (fld[p.x][p.y].unit != nullptr)
		return addAndRemoveResult::addErrorColission;

	if (fld[p.x][p.y].ntrl != nullptr)
		(*unitToAdd)(fld[p.x][p.y].ntrl);

	fld[p.x][p.y].unit = unitToAdd;
	fld[p.x][p.y].name = unitToAdd->name;

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
	if (p.x < 0 || p.y < 0 || p.x >= width || p.y >= height)
		return addAndRemoveResult::removeErrorIncorrectCoord;
	if (fld[p.x][p.y].unit == nullptr)
		return addAndRemoveResult::removeErrorNoUnit;

	if (fld[p.x][p.y].unit->from_base == true)
		base.forgetAbout(p);

	fld[p.x][p.y].unit = nullptr;
	fld[p.x][p.y].name = ' ';
	fld[p.x][p.y].effect = { 0, EffectTypes::damage };

	return addAndRemoveResult::unitRemoved;
}

addAndRemoveResult Field::createInBase(Field::UnitPtr unitToAdd, Point p)
{
	bool addRes = base.addUnit(p);
	if (addRes == false)
		return addAndRemoveResult::MaxUnitsCntError;

	unitToAdd->from_base = true;
	return addUnit(unitToAdd, p);
}

moveResult Field::moveUnit(Point from, Point to)
{
	if (from.x >= width || from.y >= height || to.x >= width || to.y >= height || from.x < 0 || from.y < 0 || to.x < 0 || to.y < 0)
		return moveResult::moveCoordinateError;

	UnitPtr unitFrom = fld[from.x][from.y].unit;
	auto prev_effect = fld[from.x][from.y].effect;

	auto removeRes = removeUnit(from);
	if (removeRes == addAndRemoveResult::removeErrorNoUnit)
		return moveResult::moveCoordinateError;

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

	auto addRes = addUnit(unitFrom, to);
	if (addRes == addAndRemoveResult::addErrorColission)
		return moveResult::moveCoordinateError;

	return moveResult::moveComplete;

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

void operator<<(std::ostream& out, Field& f)
{
	if (f.fld == nullptr)
	{
		std::cout << "\nEmpty field\n\n";
		return;
	}

	std::cout << std::string(5, ' ');
	for (size_t j = 0; j < f.width; ++j)
	{
		std::cout << j << "   ";
	}
	std::cout << "\n";

	std::cout << std::string(5, ' ');
	for (size_t j = 0; j < f.width; ++j)
	{
		std::cout << '-' << std::string(std::to_string(j).size() + 2, ' ');
	}
	std::cout << "\n";

	for (size_t i = 0; i < f.height; ++i)
	{
		std::cout << i << std::string(3 - std::to_string(i).size(), ' ');
		for (size_t j = 0; j < f.width; ++j)
		{
			std::cout << "| ";
			std::cout << f[i][j].name << std::string(std::to_string(j).size(), ' ');
		}
		std::cout << '|' << "\n";
		std::cout << std::string(5, ' ');
		for (size_t j = 0; j < f.width; ++j)
		{
			std::cout << '-' << std::string(std::to_string(j).size() + 2, ' ');
		}
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