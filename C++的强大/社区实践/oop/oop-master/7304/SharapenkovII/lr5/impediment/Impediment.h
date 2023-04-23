//
// Created by smokfyz on 10.04.19.
//

#ifndef XGAME_IMPEDIMENT_H
#define XGAME_IMPEDIMENT_H

#include <vector>
#include <algorithm>
#include "../field/Cell.h"

using namespace std;

class Impediment {

protected:
    string type_name;
    unsigned permeability;
    float probability;
    vector<shared_ptr<Cell>> filled;

public:
    virtual ~Impediment() = default;

    string getTypeName() const;
    unsigned getPermeability() const;
    float getProbability() const;

    vector<shared_ptr<Cell>> const &getFilled() const;
    void fillCell(shared_ptr<Cell>);
    void refillCell(shared_ptr<Cell>);

    virtual void update() = 0;
    virtual void generate() = 0;

};


#endif //XGAME_IMPEDIMENT_H
