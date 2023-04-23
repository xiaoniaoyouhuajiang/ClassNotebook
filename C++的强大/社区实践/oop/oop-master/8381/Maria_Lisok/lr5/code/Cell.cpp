#include "cell.h"
Cell::Cell(){
    landscape = new Forest();
}
Cell::~Cell()
{
    delete unit;
    unit  = nullptr;
    delete neutral;
    neutral = nullptr;
    delete landscape;
    landscape = nullptr;
    delete base;
    base = nullptr;
}

Cell::Cell(const Cell &cell) : unit(cell.unit->copyItem()), neutral(cell.neutral), landscape(cell.landscape),base(cell.base)
{

}

Cell::Cell(Cell &&cell) : unit(std::move(cell.unit)), neutral(std::move(cell.neutral)), landscape(std::move(cell.landscape)), base(std::move(base))
{
    cell.unit = nullptr;
    cell.neutral = nullptr;
    cell.landscape = nullptr;
    cell.base = nullptr;
}

Cell& Cell::operator= (const Cell& cell)
{
    if (&cell == this)
        return *this;
    delete unit;
    delete neutral;
    delete landscape;
    delete base;
    unit = std::move(cell.unit);
    delete cell.unit;
    neutral = std::move(cell.neutral);
    delete cell.neutral;
    landscape =std::move(cell.landscape);
    delete cell.landscape;
    base =std::move(cell.base);
    delete cell.base;
    return *this;
}

Cell& Cell::operator= (Cell&& cell)
{
    if (&cell == this)
        return *this;

    unit = std::move(cell.unit);
    neutral = std::move(cell.neutral);
    landscape = std::move(cell.landscape);
    base = std::move(cell.base);
    return *this;
}
void Cell::delUnit()
{
    delete unit;
    unit = nullptr;
}

void Cell::addNeutral(NeutralObj * obj)
{
    neutral = obj;
}

void Cell::delNeutral()
{
    delete neutral;
    neutral = nullptr;
}
void Cell::addUnit(Unit* u)
{
    unit = std::move(u);
}
bool Cell::isUnitFree() const
{
    return unit == nullptr;
}

Unit *Cell::getUnit() const
{
    return unit;
}

NeutralObj *Cell::getNeutral() const
{
    return neutral;
}

string Cell::characteristic(unsigned x, unsigned y)
{
    string chr{};
    chr.append("\nUnit:");
    if(!unit)
        chr.append("X=" + std::to_string(x) + ",Y=" + std::to_string(y) + ": no unit at this position\n");
    else
        chr.append(unit->characteristic());
    if(!neutral)
        chr.append("X=" + std::to_string(x) + ",Y=" + std::to_string(y) + ": no neutral at this position\n");
    else
        chr.append("Neutral:"+neutral->characteristic()+"\n");
    chr.append("Landscape:"+landscape->getLandscapeType());
    chr.append("\n\n");
    return chr;
}

Landscape *Cell::getLandscape() const
{
    return landscape;
}

void Cell::setLandscape(Landscape *value)
{
    landscape = value;
}

Base *Cell::getBase() const
{
    return base;
}

void Cell::setBase(Base *value)
{
    base = value;
}
