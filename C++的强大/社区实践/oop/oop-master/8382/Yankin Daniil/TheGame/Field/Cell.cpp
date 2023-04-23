#include "Cell.h"
#include "Landscape/LandscapeHeader.h"
#include "Unit/UnitHeader.h"


Cell::Cell() : point(Point(0, 0)), landscape(nullptr), unit(nullptr), building(nullptr), buildingType(OBJECT) {

}

Cell::Cell(Point point, ILandscape* landscape) : point(point), landscape(new LandscapeProxy(static_cast <Landscape*> (landscape))),
    unit(nullptr), building(nullptr), buildingType(OBJECT) {
}

Cell::Cell(Cell&& oldCell) : point(oldCell.point), landscape(oldCell.landscape), unit(oldCell.unit), building(oldCell.building), buildingType(oldCell.buildingType) {
    oldCell.landscape = nullptr;
    oldCell.unit = nullptr;
    oldCell.building = nullptr;
}

Cell::~Cell() {
    delete landscape;
}



Cell& Cell::operator=(Cell&& oldCell) {
    point = oldCell.point;
    landscape = oldCell.landscape;
    unit = oldCell.unit;
    building = oldCell.building;

    oldCell.landscape = nullptr;
    oldCell.unit = nullptr;
    oldCell.building = nullptr;

    return *this;
}



Point Cell::getPoint() {
    return point;
}

uint16_t Cell::getX() {
    return point.getX();
}

uint16_t Cell::getY() {
    return point.getY();
}


ILandscape* Cell::getLandscape() {
    return landscape;
}


bool Cell::setUnit(IUnit *unit) {
    if (isUnitFree()) {
        this->unit = unit;
        return true;
    }
    return false;
}

IUnit* Cell::getUnit() {
    return unit;
}

void Cell::removeUnit() {
    unit = nullptr;
}



bool Cell::setBase(Base* base) {
    if (isBuildingFree()) {
        this->base = base;
        this->buildingType = BASE;
        return true;
    }
    return false;
}

Base* Cell::getBase() {
    if (buildingType == BASE)
        return base;
    return nullptr;
}

void Cell::removeBase() {
    base = nullptr;
    buildingType = OBJECT;
}



bool Cell::setContext(NeutralContext* context) {
    if (isBuildingFree()) {
        this->context = context;
        this->buildingType = NEUT_OBJECT;
        return true;
    }
    return false;
}

NeutralContext* Cell::getContext() {
    if (buildingType == NEUT_OBJECT)
        return context;
    return nullptr;
}



bool Cell::isUnitFree() {
    if (unit == nullptr)
        return true;
    return false;
}

bool Cell::isBuildingFree() {
    if (building == nullptr)
        return true;
    return false;
}

uint16_t Cell::getBuildingGroupType() {
    return buildingType;
}
