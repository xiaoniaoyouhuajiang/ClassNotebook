//
// Created by smokfyz on 10.04.19.
//

#ifndef XGAME_FIELD_H
#define XGAME_FIELD_H

#include <vector>
#include "../utility/Coord.h"
#include "../field/Cell.h"
#include "../impediment/ImpedimentOrchestrator.h"

#define DEFAULT_FIELD_SIZE 20

using namespace std;

class Field {
    unsigned const field_size;
    vector<vector<shared_ptr<Cell>>> content;

    unique_ptr<ImpedimentOrchestrator> imp_orch;

    void fillContent();

public:
    explicit Field(unsigned = DEFAULT_FIELD_SIZE);

    unsigned getSize() const;

    shared_ptr<Cell> getCell(Coord);

    vector<shared_ptr<Impediment>> &getImps();

    ImpedimentOrchestrator &getImpOrch();

    void clear();

    vector<shared_ptr<Cell>> &operator[](int idx);

};


#endif //XGAME_FIELD_H
