#pragma once
#include "Shape.hpp"
#include <iostream>

class Pentagon : public Shape
{
public:
	const V5d& getDotsRadius() const;
	const V5d& getDotsAngle() const;
	void setDotsRadius(const V5d& newR);
	void setDotsAngle(const V5d& newA);
	void scale(double sc) override;
	void print() const override;
private:
	V5d R;
	V5d A;
};
