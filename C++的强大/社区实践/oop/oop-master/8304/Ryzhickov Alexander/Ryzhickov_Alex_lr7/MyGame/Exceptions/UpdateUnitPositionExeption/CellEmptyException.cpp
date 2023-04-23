//
// Created by Alex on 21.05.2020.
//

#include "CellEmptyException.h"
namespace MyGameException {
    CellEmptyException::CellEmptyException(int x, int y) : x(x), y(y) {}

    std::string CellEmptyException::what() {
        return "Unit don't exist on cell " + std::to_string(x) + ":" + std::to_string(y) + "\n";
    }
}