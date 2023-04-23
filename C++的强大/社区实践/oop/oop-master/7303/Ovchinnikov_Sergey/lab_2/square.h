#pragma once
#include "shape.h"
#include <vector>

class Square:public Shape{
public:
    Square(const Point &center,const Color& color, double _a);
    Square(const Square& square);

    void Move(const Point& p);
	void Turn(double angle);
	void Scale(double scale);

    double get_a() const;

    friend std::ostream& operator<<(std::ostream& out,const Square& square);
protected:
    std::vector<Point> tops;
    double a;
};