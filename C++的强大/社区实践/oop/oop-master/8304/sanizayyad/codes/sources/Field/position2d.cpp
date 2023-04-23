#include "position2d.hpp"


Position2D::Position2D()
{
    this->x = 0;
    this->y = 0;
}



Position2D::Position2D(int x, int y)
{
    this->x = x;
    this->y = y;
}


Position2D::Position2D(const Position2D& position)
{
    this->x = position.x;
    this->y = position.y;
}




Position2D& Position2D::operator=(const Position2D& position)
{
    if (this == &position) {
        return *this;
    }

    this->x = position.x;
    this->y = position.y;

    return *this;
}
