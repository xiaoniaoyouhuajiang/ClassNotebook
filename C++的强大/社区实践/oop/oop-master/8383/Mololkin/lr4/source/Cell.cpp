#include "Cell.h"

bool Cell::getEmptyOfCell()
{
	return this->emptyOfCell;
}

bool Cell::getIsUnitOnCell()
{
	return isUnitOnCell;
}

IUnit * Cell::getUnitOnCell()
{
	if (isUnitOnCell)
		return this->unitOnCell;
	else return nullptr;
}

Base* Cell::getBaseOnCell()
{
	if (!isUnitOnCell)
		return this->baseOnCell;
	return nullptr;
}

void Cell::setUnitOnCell(IUnit* unitOnCell)
{
	if (emptyOfCell == true && cellLandscape->canGo()) {
		this->unitOnCell = unitOnCell;
		emptyOfCell = false;
		isUnitOnCell = true;
		cellLandscape->landscapeInfluence(unitOnCell);
	}
}

void Cell::setBaseOnCell(Base* baseOnCell)
{
	if (emptyOfCell == true) {
		this->baseOnCell = baseOnCell;
		emptyOfCell = false;
		isUnitOnCell = false;
	}
}

LandscapeProxy* Cell::getCellLandscape()
{
	return this->cellLandscape;
}

IUnit* Cell::killUnitOnCell()
{
	if (isUnitOnCell && !emptyOfCell) {
		IUnit* retUnit = unitOnCell;
		unitOnCell = nullptr;
		emptyOfCell = true;
		return retUnit;
	}
	return nullptr;
	
}

void Cell::delBaseOnCell()
{
	if (!isUnitOnCell && !emptyOfCell) {
		baseOnCell = nullptr;
		emptyOfCell = true;
	}
}

std::string Cell::getCell()
{
	std::string retStr = "";
	if (emptyOfCell == true)
	{
		retStr += "__";
	}
	else if (isUnitOnCell == false)
	{
		retStr += "B";
		retStr += std::to_string(baseOnCell->getBaseNum());
	}
	else
	{
		if (this->getUnitOnCell() == nullptr) retStr += "u_";
		else {
			switch (this->getUnitOnCell()->getUnitType())
			{
			case Units::SPEARMAN:
			{
				retStr += "P";
				break;
			}
			case Units::SWORDSMAN:
			{
				retStr += "W";
				break;
			}
			case Units::ARCHER:
			{
				retStr += "A";
				break;
			}
			case Units::CROSSBOWMAN:
			{
				retStr += "S";
				break;
			}
			case Units::CATAPULT:
			{
				retStr += "C";
				break;
			}
			case Units::BALLISTA:
			{
				retStr += "X";
				break;
			}
			default: retStr += "O";
			}
			retStr += std::to_string(this->getUnitOnCell()->getTeam());

		}

	}
	retStr += " ";
	if (cellLandscape == nullptr) retStr += "NP";
	else {
		if (cellLandscape->getLandscapeType() == Landscapes::SWAMP) retStr += "SW";
		else if (cellLandscape->getLandscapeType() == Landscapes::HILLS) retStr += "HI";
		else if (cellLandscape->getLandscapeType() == Landscapes::PLAIN) retStr += "PL";
		else retStr += "XX";
	}
	return retStr;
}

Cell::Cell()
{
	unitOnCell = nullptr;
	baseOnCell = nullptr;
	emptyOfCell = true;
	isUnitOnCell = true;
	unsigned int randNum = rand() % 100 + 1;
	if (randNum < 60) { cellLandscape = new LandscapeProxy(Landscapes::PLAIN); }
	else if (randNum < 90) { cellLandscape = new LandscapeProxy(Landscapes::HILLS); }
	else cellLandscape = new LandscapeProxy(Landscapes::SWAMP);
}

Cell::~Cell()
{
	delete unitOnCell;
}

Cell::Cell(Cell& other)
{
	this->emptyOfCell = other.getEmptyOfCell();
	if (this->emptyOfCell != true) 
	{
		switch (other.getUnitOnCell()->getUnitType())
		{
			case Units::SPEARMAN:
			{
				this->unitOnCell = new Spearman(*static_cast<Spearman*>(other.getUnitOnCell()));
				break;
			}
			case Units::SWORDSMAN:
			{
				this->unitOnCell = new Swordsman(*static_cast<Swordsman*>(other.getUnitOnCell()));
				break;
			}
			case Units::ARCHER:
			{
				this->unitOnCell = new Archer(*static_cast<Archer*>(other.getUnitOnCell()));
				break;
			}
			case Units::CROSSBOWMAN:
			{
				this->unitOnCell = new Crossbowman(*static_cast<Crossbowman*>(other.getUnitOnCell()));
				break;
			}
			case Units::CATAPULT:
			{
				this->unitOnCell = new Catapult(*static_cast<Catapult*>(other.getUnitOnCell()));
				break;
			}
			case Units::BALLISTA:
			{
				this->unitOnCell = new Ballista(*static_cast<Ballista*>(other.getUnitOnCell()));
				break;
			}
		}
	}
	switch (other.getCellLandscape()->getLandscapeType())
	{
	case Landscapes::PLAIN:
	{
		this->cellLandscape = new LandscapeProxy(Landscapes::PLAIN);
		break;
	}
	case Landscapes::SWAMP:
	{
		this->cellLandscape = new LandscapeProxy(Landscapes::SWAMP);
		break;
	}
	case Landscapes::HILLS:
	{
		this->cellLandscape = new LandscapeProxy(Landscapes::HILLS);
		break;
	}
	}
}
