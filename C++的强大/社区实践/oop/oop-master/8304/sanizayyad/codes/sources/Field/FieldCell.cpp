#include "FieldCell.hpp"

using namespace unit;

FieldCell::FieldCell()
{
    empty = true;
    this->neutralObject = std::make_shared<NoObject>();
    this->landscape = std::shared_ptr<ProxyLandscape>(new ProxyLandscape);
}


FieldCell::FieldCell(const FieldCell& fieldCell)
{
    copy(fieldCell);
}


FieldCell::FieldCell(FieldCell&& fieldCell)
{
      move(fieldCell);
}


FieldCell& FieldCell::operator=(const FieldCell& fieldCell)
{
    if (this == &fieldCell) {
        return *this;
    }

    copy(fieldCell);

    return *this;
}


FieldCell& FieldCell::operator=(FieldCell&& fieldCell)
{
    if (this == &fieldCell) {
        return *this;
    }

    move(fieldCell);

    return *this;
}


void FieldCell::addUnit(std::shared_ptr<unit::Unit> unit)
{
    this->unit = unit;
    if(unit)
        this->empty = false;
}


void FieldCell::deleteUnit()
{
    this->unit = nullptr;

    this->empty = true;
}


std::shared_ptr<unit::Unit> FieldCell::getUnit()
{
    return unit;
}

bool FieldCell::isEmpty() const
{
    return empty;
}

void FieldCell::setNeutralObject(std::shared_ptr<NeutralObject> neutralObject)
{
    this->neutralObject = neutralObject;
}


std::shared_ptr<NeutralObject> FieldCell::getNeutralObject() const
{
    return neutralObject;
}


void FieldCell::deleteNeutralObject()
{
    this->neutralObject = std::make_shared<NoObject>();
}

void FieldCell::setLandscape(std::shared_ptr<Landscape> landscape)
{
    this->landscape = landscape;
}


std::shared_ptr<Landscape> FieldCell::getLandscape() const
{
    return landscape;
}
void FieldCell::copy(const FieldCell& fieldCell)
{
    if (fieldCell.landscape) {
        this->landscape = fieldCell.landscape->clone();
    }

    if (fieldCell.neutralObject) {
        this->neutralObject = fieldCell.neutralObject->clone();
    }

    this->unit = nullptr;
    this->empty = fieldCell.empty;

    if (!fieldCell.isEmpty()) {
        this->unit = fieldCell.unit->clone();
    }
}

void FieldCell::move(FieldCell& fieldCell)
{
    this->unit = nullptr;
    this->landscape = std::move(fieldCell.landscape);
    this->neutralObject = std::move(fieldCell.neutralObject);
    this->unit = std::move(fieldCell.unit);
    this->empty = fieldCell.empty;
    fieldCell.empty = true;
}

