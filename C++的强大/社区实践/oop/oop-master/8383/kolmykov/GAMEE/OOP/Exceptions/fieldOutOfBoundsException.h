#pragma once


#include <ostream>


class FieldOutOfBoundsException {
private:
    int x;
    int y;
public:
    FieldOutOfBoundsException(int x, int y);
    friend std::ostream& operator<< (std::ostream &out, const FieldOutOfBoundsException exeption);
};
