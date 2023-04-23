#ifndef NULLPOINTERMEDIATORINTOWER_H
#define NULLPOINTERMEDIATORINTOWER_H


#include <ostream>


class NullPointerMediatorInTowerException
{
    int x;
    int y;
public:
    NullPointerMediatorInTowerException(int x, int y);
    friend std::ostream& operator<< (std::ostream &out, const NullPointerMediatorInTowerException exeption);
};

#endif // NULLPOINTERMEDIATORINTOWER_H
