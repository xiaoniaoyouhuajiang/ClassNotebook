//
// Created by smokfyz on 17.05.19.
//

#ifndef XGAME_COORD_H
#define XGAME_COORD_H


class Coord {
    unsigned x;
    unsigned y;

public:
    Coord(unsigned x, unsigned y) : x(x), y(y) {}

    unsigned getX() { return x; }
    unsigned getY() { return y; }
};


#endif //XGAME_COORD_H
