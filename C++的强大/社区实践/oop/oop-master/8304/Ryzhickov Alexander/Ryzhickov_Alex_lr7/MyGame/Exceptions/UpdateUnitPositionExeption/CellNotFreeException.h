//
// Created by Alex on 21.05.2020.
//

#ifndef GAME_CELLNOTFREEEXCEPTION_H
#define GAME_CELLNOTFREEEXCEPTION_H

#include <string>
namespace MyGameException {
    class CellNotFreeException : std::exception {
    public:
        CellNotFreeException(int x, int y);

        std::string what();

    private:
        int x;
        int y;
    };
}

#endif //GAME_CELLNOTFREEEXCEPTION_H
