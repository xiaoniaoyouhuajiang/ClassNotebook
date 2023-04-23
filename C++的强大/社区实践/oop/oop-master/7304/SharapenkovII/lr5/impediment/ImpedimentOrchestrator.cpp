//
// Created by smokfyz on 17.05.19.
//

#include <cstdlib>
#include <iostream>
#include "ImpedimentOrchestrator.h"
#include "StaticImpediment.h"
#include "DynamicImpediment.h"
#include "../runtime/Game.h"
#include "../exception/Exception.h"

void ImpedimentOrchestrator::createImp(Coord c, string imp_type) {
    Game &game = Game::getGame();
    Field &field = game.getField();

    if(imp_type == "River") {
        shared_ptr<Impediment> river = make_shared<River>();

        imps.push_back(river);

        shared_ptr<Cell> cell = field.getCell(c);

        vector<shared_ptr<Cell>> reachable = cell->getReachable();;
        int next = 4;
        while (reachable.size() - 1 >= next) {
            if(!cell->getImp()) {
                cell->setImp(river);
                river->fillCell(cell);
            }
            cell = reachable[next];
            next = rand() % 2 + 4;
            reachable = cell->getReachable();
        }
        if(!cell->getImp()) {
            cell->setImp(river);
            river->fillCell(cell);
        }
    } else if(imp_type == "Mountains") {
        shared_ptr<Impediment> mountains = make_shared<Mountains>();

        imps.push_back(mountains);

        shared_ptr<Cell> cell = field.getCell(c);

        vector<shared_ptr<Cell>> reachable = cell->getReachable();;
        int next = rand() % 6;
        while (reachable.size() - 1 >= next) {
            if(!cell->getImp()) {
                cell->setImp(mountains);
                mountains->fillCell(cell);
            }
            cell = reachable[next];
            next = rand() % 6;
            reachable = cell->getReachable();
        }
    } else if(imp_type == "Forest") {
        shared_ptr<Impediment> forest = make_shared<Forest>();

        imps.push_back(forest);

        shared_ptr<Cell> cell = field.getCell(c);

        vector<shared_ptr<Cell>> reachable = cell->getReachable();;
        int next = rand() % 6;
        while (reachable.size() - 1 >= next) {
            if(!cell->getImp()) {
                cell->setImp(forest);
                forest->fillCell(cell);
            }
            cell = reachable[next];
            next = rand() % 6;
            reachable = cell->getReachable();
        }
    } else if(imp_type == "Swamp") {
        shared_ptr<Impediment> swamp = make_shared<Swamp>();

        imps.push_back(swamp);

        shared_ptr<Cell> cell = field.getCell(c);

        vector<shared_ptr<Cell>> reachable = cell->getReachable();;
        int next = rand() % 6;
        while (reachable.size() - 1 >= next) {
            if(!cell->getImp()) {
                cell->setImp(swamp);
                swamp->fillCell(cell);
            }
            cell = reachable[next];
            next = rand() % 6;
            reachable = cell->getReachable();
        }
    } else if(imp_type == "Rain") {
        shared_ptr<Impediment> rain = make_shared<Rain>();

        imps.push_back(rain);

        shared_ptr<Cell> cell = field.getCell(c);

        vector<shared_ptr<Cell>> reachable = cell->getReachable();;
        int next = rand() % 6;
        while (reachable.size() - 1 >= next) {
            if(!cell->getImp()) {
                cell->setImp(rain);
                rain->fillCell(cell);
            }
            cell = reachable[next];
            next = rand() % 6;
            reachable = cell->getReachable();
        }
    } else if(imp_type == "Snow") {
        shared_ptr<Impediment> snow = make_shared<Snow>();

        imps.push_back(snow);

        shared_ptr<Cell> cell = field.getCell(c);

        vector<shared_ptr<Cell>> reachable = cell->getReachable();;
        int next = rand() % 6;
        while (reachable.size() - 1 >= next) {
            if(!cell->getImp()) {
                cell->setImp(snow);
                snow->fillCell(cell);
            }
            cell = reachable[next];
            next = rand() % 6;
            reachable = cell->getReachable();
        }
    } else if(imp_type == "Fog") {
        shared_ptr<Impediment> fog = make_shared<Fog>();

        imps.push_back(fog);

        shared_ptr<Cell> cell = field.getCell(c);

        vector<shared_ptr<Cell>> reachable = cell->getReachable();;
        int next = rand() % 6;
        while (reachable.size() - 1 >= next) {
            if(!cell->getImp()) {
                cell->setImp(fog);
                fog->fillCell(cell);
            }
            cell = reachable[next];
            next = rand() % 6;
            reachable = cell->getReachable();
        }
    } else {
        throw Exception("Unknown impediment type: " + imp_type);
    }
}

void ImpedimentOrchestrator::deleteImp(shared_ptr<Impediment> imp) {
    for(auto &cell : imp->getFilled())
        cell->deleteImp();

    imps.erase(std::remove(imps.begin(), imps.end(), imp), imps.end());
}

void ImpedimentOrchestrator::updateImps() {
    for(auto &imp : imps) {
        imp->update();
    }
}

void ImpedimentOrchestrator::clearAllImp() {
    for(auto &imp : imps)
        for(auto &cell : imp->getFilled())
            cell->deleteImp();

    imps.clear();
}

vector<shared_ptr<Impediment>>& ImpedimentOrchestrator::getImps() { return imps; }