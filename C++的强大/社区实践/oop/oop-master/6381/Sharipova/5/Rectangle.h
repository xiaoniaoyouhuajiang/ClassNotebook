#include "Shape.h"
#include <iostream>

class Rectangle : public Shape
{
private:
    float coordinates[4][2];
public:
    void Print();
    Rectangle(float(&coord)[4][2], int c = 0);
    ~Rectangle() { }
    void Move(float new_x, float new_y);
    void Scale(float k);
    void Turn(float angle);
};

