//
// Created by anton on 6/2/20.
//

#ifndef OOPROJECT_NOTERRAINEXCEPTION_H
#define OOPROJECT_NOTERRAINEXCEPTION_H


#include <ostream>

class NoTerrainException {
public:
    NoTerrainException(int x, int y) : x(x), y(y) {}

    friend std::ostream &operator<<(std::ostream &os, const NoTerrainException &exception) {
        os << "No terrain at position x: " << exception.x << " y: " << exception.y;
        return os;
    }

private:
    int x;
    int y;
};


#endif //OOPROJECT_NOTERRAINEXCEPTION_H
