//
// Created by smokfyz on 12.04.19.
//

#include <algorithm>
#include <iostream>
#include "../runtime/Game.h"
#include "Player.h"
#include "../exception/Exception.h"

unsigned Player::player_num = 0;

Player::Player(string &&n, string &&c) : name(n), color(c) {
    player_id = player_num++;

    Game &game = Game::getGame();
    Field &field = game.getField();
}

unsigned Player::getId() { return player_id; }

string Player::getName() { return name; }

string Player::getColor() { return color; }

void Player::createUnit(Coord c, string unit_type) {
    shared_ptr<Unit> unit;
    if(unit_type == "Archer")
        unit = make_shared<Archer>();
    else if(unit_type == "Tank")
        unit = make_shared<Tank>();
    else if(unit_type == "Knight")
        unit = make_shared<Knight>();
    else if(unit_type == "King")
        unit = make_shared<King>();
    else if(unit_type == "Priest")
        unit = make_shared<Priest>();
    else if(unit_type == "Killer")
        unit = make_shared<Killer>();
    else
        throw Exception("Unknown unit type: " + unit_type);

    addUnit(unit);
    placeUnit(c, unit);
}
void Player::createUnit(shared_ptr<Cell> cell, shared_ptr<Unit> unit) {
    addUnit(unit);
    placeUnit(Coord(cell->getX(), cell->getY()), unit);
}
void Player::addUnit(shared_ptr<Unit> unit) { units.push_back(unit); }
bool Player::hasUnit(shared_ptr<Unit> unit) { return find(units.begin(), units.end(), unit) != units.end(); }
void Player::placeUnit(Coord c, shared_ptr<Unit> unit) {
    Game &game = Game::getGame();
    Field &field = game.getField();

    shared_ptr<Cell> cell = field.getCell(c);
    cell->setUnit(unit);
    unit->setPosition(cell);
}
void Player::resetUnits() {
    for(auto &unit : units) {
        unit->reset();
    }
}

void Player::findPaths(shared_ptr<Cell> &cell, unsigned energy, int deep) {
    unsigned permeability = 5;

    if(cell->hasImp()) permeability = cell->getImp()->getPermeability();

    if(find(paths.begin(), paths.end(), cell) != paths.end() || energy < permeability || deep < 0) return;

    vector<shared_ptr<Cell>> reachable = cell->getReachable();

    paths.push_back(cell);
    energy_loss.push_back(energy - permeability);
    for(auto &next_cell : reachable)
        findPaths(next_cell, energy - permeability, deep - 1);
}

vector<shared_ptr<Cell>>& Player::getPaths() { return paths; }

unsigned Player::getEnergyLoss(shared_ptr<Cell> c) {
    if(hasPath(c)) {
        auto it = find(paths.begin(), paths.end(), c);
        return energy_loss[distance(paths.begin(), it)];
    } else {
        return 0;
    }
}

bool Player::hasPath(shared_ptr<Cell> c) { return find(paths.begin(), paths.end(), c) != paths.end(); }

void Player::clearPaths() {
    paths.clear();
    energy_loss.clear();
}

vector<shared_ptr<Unit>>& Player::getUnits() { return units; }