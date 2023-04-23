#pragma once
#include "figure.h"
#include "point.h"

class pentagon : public figure
{
private:
    point vertexes[5];
    point get_center() const;

public:
	pentagon(const point (&vertexes)[5], const Color &color);
    pentagon(const pentagon& other);
    pentagon& operator=(const pentagon& other);

	virtual void scale(double num) override;
	virtual void turn(double angle) override;
	virtual void shift(double num1, double num2) override;

    virtual double distance(int x, int y) override;
    virtual void print(std::ostream &os) override;
};
