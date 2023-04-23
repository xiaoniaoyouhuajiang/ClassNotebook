#pragma once

#ifndef OOP_RegPentagon_H
#define OOP_RegPentagon_H
#include "Pentagon.h"

class RegPentagon : public Pentagon {

private:
	double radius;
public:
	int Id;
	RegPentagon(const Point &center, const Point &point, const Color &color);
	double getRadius() const;

};
#endif
