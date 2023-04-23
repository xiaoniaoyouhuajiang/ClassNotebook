
//#include "stdafx.h"
#include <iostream>
#include <cmath>
//#include <conio.h>

class Shape
{
protected:
    int color;
    float left_x, left_y, right_x, right_y;

public:
    virtual void Print() = 0;
    void Draw(int new_color = 0) { color = new_color; }
    int getDraw() { return color; }
    virtual void Move(float new_x, float new_y) = 0;
    virtual void Scale(float k) = 0;
    virtual void Turn(float angle) = 0;
};



