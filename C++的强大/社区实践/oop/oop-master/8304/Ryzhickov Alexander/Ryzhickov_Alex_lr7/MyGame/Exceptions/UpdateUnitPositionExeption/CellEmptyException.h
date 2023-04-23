//
// Created by Alex on 21.05.2020.
//

#ifndef GAME_CELLEMPTYEXCEPTION_H
#define GAME_CELLEMPTYEXCEPTION_H

#include <string>
namespace MyGameException {
    class CellEmptyException : public std::exception {
    public:
        CellEmptyException(int x, int y);

        std::string what();

    private:
        int x;
        int y;
    };
}

#endif //GAME_CELLEMPTYEXCEPTION_H
