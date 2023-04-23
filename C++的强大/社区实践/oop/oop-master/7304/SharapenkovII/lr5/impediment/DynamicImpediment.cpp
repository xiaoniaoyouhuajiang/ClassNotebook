//
// Created by smokfyz on 13.05.19.
//

#include "DynamicImpediment.h"
//
// Created by smokfyz on 13.05.19.
//

#include <iostream>
#include <cstdlib>
#include "StaticImpediment.h"
#include "../runtime/Game.h"

void DynamicImpediment::generate() {}

Rain::Rain()  {
    type_name = "Rain";
    permeability = 70;
    probability = 0.5;
}

void Rain::update() {
    vector<shared_ptr<Cell>> filled_copy = filled;
    unsigned next = rand() % 24;

    for(auto &cell : filled_copy) {
        for(auto &reachable_cell : cell->getReachable()) {
            if(next == 0 && !reachable_cell->getImp()) {
                reachable_cell->setImp(cell->getImp());
                fillCell(reachable_cell);
            }
            next = rand() % 24;
        }
        if(next == 2) {
            cell->deleteImp();
            refillCell(cell);
        }
    }
}

Snow::Snow() {
    type_name = "Snow";
    permeability = 40;
    probability = 0.2;
}

void Snow::update() {
    vector<shared_ptr<Cell>> filled_copy = filled;
    unsigned next = rand() % 12;

    for(auto &cell : filled_copy) {
        for(auto &reachable_cell : cell->getReachable()) {
            if(next == 0 && !reachable_cell->getImp()) {
                reachable_cell->setImp(cell->getImp());
                fillCell(reachable_cell);
            }
            next = rand() % 12;
        }
        if(next == 2) {
            cell->deleteImp();
            refillCell(cell);
        }
    }
}

Fog::Fog() {
    type_name = "Fog";
    permeability = 40;
    probability = 0.1;
}

void Fog::update() {
    vector<shared_ptr<Cell>> filled_copy = filled;
    unsigned next = rand() % 6;

    for(auto &cell : filled_copy) {
        for(auto &reachable_cell : cell->getReachable()) {
            if(next == 0 && !reachable_cell->getImp()) {
                reachable_cell->setImp(cell->getImp());
                fillCell(reachable_cell);
            }
            next = rand() % 6;
        }
        if(next == 2) {
            cell->deleteImp();
            refillCell(cell);
        }
    }
}