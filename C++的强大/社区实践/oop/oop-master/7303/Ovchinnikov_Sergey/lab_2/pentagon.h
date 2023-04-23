#pragma once
#include "shape.h"
#include <vector>

class Pentagon:public Shape{
public:
    Pentagon(const Point &center,const Color& color, double _radius);
    Pentagon(const Pentagon& pentagon);

    void Move(const Point& p);
	void Turn(double angle);
	void Scale(double scale);

    double get_radius() const;

    friend std::ostream& operator<<(std::ostream& out,const Pentagon& pentagon);
protected:
    std::vector<Point> tops;
    double radius;

};