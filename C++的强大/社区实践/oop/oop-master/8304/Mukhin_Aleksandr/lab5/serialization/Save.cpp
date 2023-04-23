#include "Save.h"

Save::Save(ProxyBoardfield* board, Base* base) {
    this->base = base;
    this->board = board;

    output = std::ofstream("save.txt", std::ios::out | std::ios::trunc);
    output << *base << std::endl;
    output << *board;
    input = std::ifstream("save.txt");
}

Save::~Save() {
    output.close();
    input.close();
}