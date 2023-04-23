//
// Created by shenk on 03.05.2020.
//

#ifndef UNTITLED13_GAMEFIELDOUTOFRANGEEXCEPTION_H
#define UNTITLED13_GAMEFIELDOUTOFRANGEEXCEPTION_H

#include <exception>

class GameFieldOutOfRangeException: std::exception {

public:

    int x;
    int y;

    GameFieldOutOfRangeException(int x, int y): x(x), y(y){}

};


#endif //UNTITLED13_GAMEFIELDOUTOFRANGEEXCEPTION_H
