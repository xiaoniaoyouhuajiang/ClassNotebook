//
// Created by smokfyz on 17.05.19.
//

#ifndef XGAME_IMPEDIMENTORCHESTRATOR_H
#define XGAME_IMPEDIMENTORCHESTRATOR_H

#include <vector>
#include <memory>
#include "Impediment.h"
#include  "../utility/Coord.h"

using namespace std;

class ImpedimentOrchestrator {
    vector<shared_ptr<Impediment>> imps;

public:
    void createImp(Coord, string);
    void deleteImp(shared_ptr<Impediment>);
    void updateImps();

    void clearAllImp();

    vector<shared_ptr<Impediment>> &getImps();
};


#endif //XGAME_IMPEDIMENTORCHESTRATOR_H
