#pragma once
#include "shape.h"
#include <vector>

class Star:public Shape{
public:
    Star(const Point &center,const Color& color ,double _r1, double _r2,  double angle = 0);
    Star(const Star& star);

    void Move(const Point& p);
	void Turn(double angle);
	void Scale(double scale);

    double get_radius1() const;
    double get_radius2() const;

    Star operator+(const Star& star);


    friend std::ostream& operator<<(std::ostream& out,const Star& star);
protected:
    std::vector<Point> tops1,tops2;
    double radius1;
    double radius2;

};