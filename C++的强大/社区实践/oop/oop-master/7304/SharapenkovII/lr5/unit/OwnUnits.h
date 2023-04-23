//
// Created by smokfyz on 23.05.19.
//

#ifndef XGAME_OWNUNITS_H
#define XGAME_OWNUNITS_H

#include "Unit.h"


class OwnUnits {
    vector<shared_ptr<Unit>> own_units;

public:
    void createUnit(string, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned);
    shared_ptr<Unit> getLast();
    vector<shared_ptr<Unit>> &getOwnUnits();

};


#endif //XGAME_OWNUNITS_H
