#ifndef STAR_H
#define STAR_H
#include "shape.h"
#include "point.h"
#include <string>
#include "pentagon.h"
#include <iostream>

using namespace std;

class Star :public Shape {
private:
	int starAngle = 0; 
	double radius;

public:
	Star(Point current_center, int angle, double scale, int radius);
	void Scale(double scale) override;
	void move(Point new_center) override;
	void print(ostream &ost) override;
	void rotate(int NewAngle) override;
};


#endif //STAR_H