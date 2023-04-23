#ifndef REGULARPENTAGON_HPP_INCLUDED
#define REGULARPENTAGON_HPP_INCLUDED

#include "shape.hpp"
#include "Pentagon.hpp"



class RegularPentagon : public Pentagon
{
public:
    RegularPentagon(Point vertex1, double length, const std::string &colour) : Pentagon(vertex1,
                                                                                 step2(vertex1, length),
                                                                                 step4(step2(vertex1, length), length),
                                                                                 step5(step4(step2(vertex1, length), length), length),
                                                                                 step3(vertex1, length),
                                                                                 colour
                                                                                 ) {};

private:
	Point step2(Point vertex, double length)
	{
		return Point{ vertex.x + length, vertex.y };
	}

	Point step3(Point vertex, double length)
	{
		double fi = PI / 10;
		return Point{ vertex.x - length*sin(fi), vertex.y - length*cos(fi) };
	}

	Point step4(Point vertex, double length)
	{
		double fi = PI / 10;
		return Point{ vertex.x + length*sin(fi), vertex.y - length*cos(fi) };
	}

	Point step5(Point vertex, double length)
	{
		double fi = PI / 5;
		return Point{ vertex.x - length*cos(fi), vertex.y - length*sin(fi) };
	}

};



#endif // REGULARPENTAGON_HPP_INCLUDED
