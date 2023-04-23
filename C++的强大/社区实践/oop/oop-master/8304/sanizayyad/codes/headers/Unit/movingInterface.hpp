
#ifndef movingInterface_hpp
#define movingInterface_hpp

#include "position2d.hpp"

#include <stdio.h>
#include "iostream"

constexpr const char* MOVE_TOP = "move top";
constexpr const char* MOVE_BOTTOM = "move bottom";
constexpr const char* MOVE_LEFT = "move left";
constexpr const char* MOVE_RIGHT = "move right";
constexpr const char* CREATE_UNIT = "create_unit";



class MovingInterface
{
public:
    virtual ~MovingInterface() = default;
    
    virtual bool moveLeft() = 0;
    virtual bool moveRight() = 0;
    virtual bool moveTop() = 0;
    virtual bool moveBottom() = 0;
    
};


#endif /* movingInterface_hpp */
