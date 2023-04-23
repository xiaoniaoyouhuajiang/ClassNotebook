//
// Created by Alex on 21.05.2020.
//

#ifndef GAME_UPDATEUNITPOSITIONEXCEPTION_H
#define GAME_UPDATEUNITPOSITIONEXCEPTION_H

#include <string>
using namespace std;
namespace MyGameException {
    class UpdateUnitPositionException : public std::exception {
    public:
        UpdateUnitPositionException(int newX, int newY, int fieldWidth, int fieldHeight, int code);

        std::string what();

    private:
        int x;
        int y;
        int fieldWidth;
        int fieldHeight;
        int code;
    };
}

#endif //GAME_UPDATEUNITPOSITIONEXCEPTION_H
