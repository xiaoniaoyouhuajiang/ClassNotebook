
#include <iostream>
#include "Shape.h"
class Pentagram : public Shape
{
private:
    float coordinates[5][2];
public:
    void Print();
    Pentagram(float(&coord)[5][2], int c = 0);
    ~Pentagram() { }
    void Move(float new_x, float new_y);
    void Scale(float k);
    void Turn(float angle);
};
