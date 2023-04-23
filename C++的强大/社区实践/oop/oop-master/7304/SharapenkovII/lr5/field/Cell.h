//
// Created by smokfyz on 10.04.19.
//

#ifndef XGAME_CELL_H
#define XGAME_CELL_H

#include <memory>
#include <vector>
#include "../utility/Coord.h"

using namespace std;

class Impediment;
class Unit;

class Cell {
    Coord coord;
    shared_ptr<Unit> unit;
    shared_ptr<Impediment> imp;

    vector<shared_ptr<Cell>> reachable;

public:
    explicit Cell(Coord);


    unsigned getX();
    unsigned getY();

    shared_ptr<Unit> getUnit();
    void setUnit(shared_ptr<Unit>);
    void deleteUnit();
    bool hasUnit();

    shared_ptr<Impediment> getImp();
    void setImp(shared_ptr<Impediment>);
    void deleteImp();
    bool hasImp();

    vector<shared_ptr<Cell>> &getReachable();
};


#endif //XGAME_CELL_H
