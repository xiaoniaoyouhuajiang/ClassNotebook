//
// Created by user on 31.03.19.
//

#ifndef OOP_2_RIGHT_TRIANGLE_H
#define OOP_2_RIGHT_TRIANGLE_H

#include "Triangle.h"
class Right_Triangle : public Triangle {
public:
    Right_Triangle(Point center, Color color, double a, double b);



    friend std::ostream &operator<<(std::ostream &out, Right_Triangle &right_triangle);

};

#endif //OOP_2_RIGHT_TRIANGLE_H
