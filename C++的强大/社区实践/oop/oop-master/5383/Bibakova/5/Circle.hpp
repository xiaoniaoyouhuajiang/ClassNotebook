#ifndef CIRCLE_HPP_INCLUDED
#define CIRCLE_HPP_INCLUDED

#include "shape.hpp"

class Circle : public Shape
{
private:
    Point center;
    double radius;
public:
    Circle(Point cent, double rad, const std::string &colour) : Shape(colour)
    {
	   assert(rad > 0);
        radius = rad;
        center = cent;
    };

    void move(Point destination)
    {
        this->center = destination;
    };

    void rotate(double angle) {};

    void zoom(double k)
    {
        this->radius *= k;
    };

	std::ostream &print(std::ostream &out) const
	{
		out << std::endl << "#" << this->getId() << " Circle colour:  " << this->colour << std::endl << "Center: (" << this->center.x << ", " << this->center.y << ")      R = " << this->radius << std::endl <<std::endl;
		return out;
	}

    /*friend std::ostream &operator<<(std::ostream &output, const Shape &c)
    {
		return c.print(output);
    };*/

	double oxPrLength() const
	{
		return (2 * this->radius);
	};

	bool equalÎxProjectionLength(const Shape& c) const
	{
		return ((2 * radius) == c.oxPrLength());
	};
};

#endif // CIRCLE_HPP_INCLUDED
