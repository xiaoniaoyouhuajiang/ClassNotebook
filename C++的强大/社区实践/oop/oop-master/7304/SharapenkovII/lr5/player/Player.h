//
// Created by smokfyz on 12.04.19.
//

#ifndef XGAME_PLAYER_H
#define XGAME_PLAYER_H

#include <memory>
#include <string>
#include <vector>
#include "../field/Cell.h"

using namespace std;

class Player {
    static unsigned player_num;
    unsigned player_id;
    string name;
    string color;

    vector<shared_ptr<Unit>> units;

    vector<shared_ptr<Cell>> paths;
    vector<unsigned> energy_loss;

public:
    explicit Player(string &&, string &&);
    virtual ~Player() = default;

    unsigned getId();
    string getName();
    string getColor();

    void createUnit(Coord, string);
    void createUnit(shared_ptr<Cell>, shared_ptr<Unit>);
    void addUnit(shared_ptr<Unit>);
    bool hasUnit(shared_ptr<Unit>);
    void placeUnit(Coord, shared_ptr<Unit>);
    void resetUnits();

    void findPaths(shared_ptr<Cell>&, unsigned, int);
    vector<shared_ptr<Cell>> &getPaths();
    unsigned getEnergyLoss(shared_ptr<Cell>);
    bool hasPath(shared_ptr<Cell>);
    void clearPaths();

    vector<shared_ptr<Unit>> &getUnits();
};


#endif //XGAME_PLAYER_H
