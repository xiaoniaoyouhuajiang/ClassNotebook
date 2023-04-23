#ifndef IMOVABLE_H
#define IMOVABLE_H

#include "Field/point2d.h"


constexpr const char* MOVE_TOP = "move top";
constexpr const char* MOVE_BOTTOM = "move bottom";
constexpr const char* MOVE_LEFT = "move left";
constexpr const char* MOVE_RIGHT = "move right";


class IMovable
{
public:
    virtual ~IMovable() = default;
    
    virtual bool moveLeft() = 0;
    virtual bool moveRight() = 0;
    virtual bool moveTop() = 0;
    virtual bool moveBottom() = 0;
};

#endif // IMOVABLE_H
