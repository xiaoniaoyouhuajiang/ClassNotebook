//
// Created by smokfyz on 10.04.19.
//

#include <iostream>
#include "Cell.h"
#include "../gui/UI.h"
#include "../runtime/Game.h"

Cell::Cell(Coord c) : coord(c) {
    unit = shared_ptr<Unit>(nullptr);
    imp = shared_ptr<Impediment>(nullptr);
}

unsigned Cell::getX() { return coord.getX(); }
unsigned Cell::getY() { return coord.getY(); }

shared_ptr<Unit> Cell::getUnit() { return unit; }
void Cell::setUnit(shared_ptr<Unit> new_unit) { unit.swap(new_unit); }
void Cell::deleteUnit() { unit.reset(); }
bool Cell::hasUnit() { return !!unit; }

shared_ptr<Impediment> Cell::getImp() { return imp; }
void Cell::setImp(shared_ptr<Impediment> new_imp) { imp.swap(new_imp); }
void Cell::deleteImp() { imp.reset(); }
bool Cell::hasImp() { return !!imp; }

vector<shared_ptr<Cell>> &Cell::getReachable() { return reachable; }