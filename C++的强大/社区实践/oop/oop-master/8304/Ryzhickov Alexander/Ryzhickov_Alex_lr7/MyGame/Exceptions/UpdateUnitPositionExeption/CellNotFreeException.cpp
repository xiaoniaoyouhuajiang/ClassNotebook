//
// Created by Alex on 21.05.2020.
//

#include "CellNotFreeException.h"
namespace MyGameException {
    CellNotFreeException::CellNotFreeException(int x, int y) : x(x), y(y) {}

    std::string CellNotFreeException::what() {
        return "Cell " + std::to_string(x) + ":" + std::to_string(y) + " is occupied by another Unit\n";
    }
}