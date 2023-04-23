#ifndef LAB2_SAVE_H
#define LAB2_SAVE_H

#include "ProxyBoardfield.h"

class Save {
private:
    ProxyBoardfield* board = nullptr;
    Base* base = nullptr;
    std::ofstream output;
    std::ifstream input;
    friend class Originator;

public:
    Save(ProxyBoardfield* board, Base* base);
    ~Save();
};


#endif
