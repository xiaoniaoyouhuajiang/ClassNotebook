#ifndef LAB2_ORIGINATOR_H
#define LAB2_ORIGINATOR_H

#include "ProxyBoardfield.h"
#include "Save.h"
#include <regex>

class Originator {
private:
    ProxyBoardfield* board = nullptr;
    Base* base = nullptr;

public:
    Originator(ProxyBoardfield* board, Base* base) : board(board), base(base) {}

    std::shared_ptr<Save> save();
    void load(std::shared_ptr<Save> save);
};


#endif
