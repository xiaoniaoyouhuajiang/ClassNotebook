#pragma once
#include "Shape.hpp"

class RegPentagon : public Shape
{
public:
	double getDotsRadius() const;
	void setDotsRadius(double newR);
	void print() const override;
	void scale(double sc) override;
private:
	double R;
};
