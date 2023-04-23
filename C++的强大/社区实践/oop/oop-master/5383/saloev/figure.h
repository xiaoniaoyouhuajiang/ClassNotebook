#pragma once
#include <string>

using namespace std;

struct Color
{
	unsigned char r, g, b;
	Color(unsigned char _r = 0, unsigned char _g = 0, unsigned char _b = 0) : r(_r), g(_g), b(_b) {}
};

class figure
{

private:

	double alpha, num;

protected:
	virtual void print(std::ostream &os) = 0;
	Color m_color;
	static size_t count;
	size_t m_id;

public:

	void setColor(const Color color);
	Color getColor() const;

	figure();

	figure(const Color &color);

	double getAngle();

	void setAngle(double alpha);

	virtual void scale(double num) = 0;

	virtual void turn(double angle) = 0;

	virtual void shift(double num1, double num2) = 0;

	virtual double distance(int x, int y) = 0;

	friend std::ostream &operator << (std::ostream &os, figure &f);

	size_t getId() const;
};
