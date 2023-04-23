#ifndef LAB2_FACADE_H
#define LAB2_FACADE_H


#include "Base.h"
#include "Boardfield.h"

class Facade {
private:
    Base* base = nullptr;
    Boardfield* board = nullptr;

public:
    Facade(Base* base, Boardfield* board) : base(base), board(board) {}
    bool fill_board();
};


#endif
