#pragma once
#include "figure.h"
#include "point.h"

class circle : public figure
{
private:
    point center;
    double radius;
    point get_center() const;

public:
	circle(const point &center, double radius, const Color &color);
    circle(const circle& other);
    circle& operator=(const circle& other);

	virtual void scale(double num) override;
	virtual void turn(double angle) override;
	virtual void shift(double num1, double num2) override;

    virtual double distance(int x, int y) override;
    virtual void print(std::ostream &os) override;
};
