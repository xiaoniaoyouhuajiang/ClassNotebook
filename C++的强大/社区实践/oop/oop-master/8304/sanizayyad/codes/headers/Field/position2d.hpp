#ifndef position2d_hpp
#define position2d_hpp

#include <stdio.h>

class Position2D
{
public:
    explicit Position2D();
    explicit Position2D(int x, int y);
    
    Position2D(const Position2D& position);
    Position2D& operator=(const Position2D& point);
    
    int x;
    int y;
};


#endif /* position2d_hpp */
