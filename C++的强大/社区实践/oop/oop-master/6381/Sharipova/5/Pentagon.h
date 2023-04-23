#include "Shape.h"
#include <ostream>

class Pentagon : public Shape
{
private:
    float coordinates[5][2];
public:
    void Print();
    Pentagon(float(&coord)[5][2], int c = 0);
    ~Pentagon() { }
    void Move(float new_x, float new_y);
    void Scale(float k);
    void Turn(float angle);
};