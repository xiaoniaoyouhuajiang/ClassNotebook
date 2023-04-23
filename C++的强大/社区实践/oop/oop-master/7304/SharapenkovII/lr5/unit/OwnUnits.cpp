//
// Created by smokfyz on 23.05.19.
//

#include <iostream>
#include "OwnUnits.h"

void OwnUnits::createUnit(string name, unsigned at, unsigned ra, unsigned ar, unsigned h, unsigned e, unsigned s) {
    shared_ptr<Unit> unit = make_shared<OwnUnit>(name, at, ra, ar, h, e, s);

    own_units.push_back(unit);
}

shared_ptr<Unit> OwnUnits::getLast() {
    return own_units[own_units.size() - 1];
}

vector<shared_ptr<Unit>> &OwnUnits::getOwnUnits() { return own_units; }