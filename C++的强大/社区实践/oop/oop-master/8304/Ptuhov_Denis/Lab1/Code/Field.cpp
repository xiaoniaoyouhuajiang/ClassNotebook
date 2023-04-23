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
}

void Field::swap(Field& other)
{
	std::swap(units_cnt, other.units_cnt);
	std::swap(width, other.width);
	std::swap(height, other.height);
	std::swap(fld, other.fld);
}

Field::Field(Field const& other)
{
	fld = other.fld;
	units_cnt = other.units_cnt;
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
	if (units_cnt == 0)
		return addAndRemoveResult::MaxUnitsCntError;

	if (p.x < 0 || p.y < 0 || p.x >= width || p.y >= height)
		return addAndRemoveResult::addErrorIncorrectCoord;

	if (fld[p.x][p.y].unit != nullptr)
		return addAndRemoveResult::addErrorColission;

	--units_cnt;
	fld[p.x][p.y].unit = unitToAdd;
	fld[p.x][p.y].name = unitToAdd->name;

	return addAndRemoveResult::unitAdded;
}

addAndRemoveResult Field::removeUnit(Point p)
{
	if (p.x < 0 || p.y < 0 || p.x >= width || p.y >= height)
		return addAndRemoveResult::removeErrorIncorrectCoord;
	if (fld[p.x][p.y].unit == nullptr)
		return addAndRemoveResult::removeErrorNoUnit;

	++units_cnt;
	fld[p.x][p.y].unit = nullptr;
	fld[p.x][p.y].name = ' ';

	return addAndRemoveResult::unitRemoved;
}

moveResult Field::moveUnit(Point from, Point to)
{
	if (from.x >= width || from.y >= height || to.x >= width || to.y >= height || from.x < 0 || from.y < 0 || to.x < 0 || to.y < 0)
		return moveResult::moveCoordinateError;
	UnitPtr unitFrom = fld[from.x][from.y].unit;
	auto removeRes = removeUnit(from);
	if (removeRes == addAndRemoveResult::removeErrorNoUnit)
		return moveResult::moveCoordinateError;

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
	f.units_cnt = 0;
}

bool Field::empty() const
{
	return height == 0 && width == 0;
}

maxUnitsCntResult Field::setMaxUnitsCnt(int new_units_cnt)
{
	if (new_units_cnt < 0)
		return maxUnitsCntResult::incorrectData;

	units_cnt = new_units_cnt;
	return maxUnitsCntResult::dataCorrect;
}

int Field::getMaxUnitsCnt() const
{
	return units_cnt;
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


