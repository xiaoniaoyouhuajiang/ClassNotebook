#ifndef LAB2_CELL_H
#define LAB2_CELL_H
#include <iostream>
#include "NeutralObject.h"
#include "Unit.h"
#include "Base.h"
#include "Fire.h"
#include "Landscape.h"
#include "NeutralObject.h"

class Base;
class Cell {
public:
    Cell() = default;

    std::shared_ptr<Unit> unit = nullptr;

    std::shared_ptr<Landscape> landscape = nullptr;
    std::string landscape_symbol{};

    Base* base = nullptr;
    std::string base_symbol{};

    std::shared_ptr<NeutralObject> neutral_object = nullptr;
    std::string neutral_object_symbol{};

    friend std::ostream& operator<<(std::ostream&, Cell&);
    Cell& operator[] (std::shared_ptr<NeutralObject>);
    Cell& operator[] (Cell&);
};


#endif
