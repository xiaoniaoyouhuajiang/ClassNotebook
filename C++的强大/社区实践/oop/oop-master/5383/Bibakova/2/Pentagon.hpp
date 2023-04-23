#ifndef PENTAGON_HPP_INCLUDED
#define PENTAGON_HPP_INCLUDED

#include "shape.hpp"
#include <math.h>

class Pentagon : public Shape
{
protected:
    const static int n = 5;
    Point vertex[n];
    //Point vertex1, vertex2, vertex3, vertex4, vertex5;
public:
    Pentagon(Point vertex1, Point vertex2, Point vertex3, Point vertex4, Point vertex5, const std::string &colour) : Shape(colour)
    {
        this->vertex[0] = vertex1;
        this->vertex[1] = vertex2;
        this->vertex[2] = vertex3;
        this->vertex[3] = vertex4;
        this->vertex[4] = vertex5;
    };

	/*Pentagon(Point v[n], const std::string &colour) : Shape(colour)
	{
		for (int i = 0; i < n; i++)
		{
			this->vertex[i] = v[i];
		};
	};*/

    /*void move(Point destination)
    {
        Point delta = delta(this.vertex1, destination);
        this.vertex1 = destination;
        this.vertex2 += delta;
        this.vertex3 += delta;
        this.vertex4 += delta;
        this.vertex5 += delta;
    };*/

   /* void move(Point destination)
    {
        int i = 0;
        Point delta = dif(this->vertex[i], destination);
        this->vertex[i] = destination;
        for (i = 1; i < n; i++)
        {
            this->vertex[i] += delta;
        }
    };*/

	void move(Point destination)
    {
        Point delta = dif(this->center(), destination);
        for (int i = 0; i < n; i++)
        {
            this->vertex[i] += delta;
        }
    };	

	Point center()
	{
		Point c = this->vertex[0];
		for (int i = 1; i < n; i++)
		{
			c += this->vertex[i];
		};
		c.x = (c.x)/n;
		c.y = (c.y)/n;
		return c;
	};

    void rotate(double angle)
    {
        Point rotationMatrix = {cos(angle), sin(angle)};
        Point backup = this->vertex[0];
        Point tmp;
        this->move(dif(backup, backup));
        for (int i = 1; i < n; i++)
        {
            tmp.x = this->vertex[i].x * rotationMatrix.x - this->vertex[i].y * rotationMatrix.y;
            tmp.y = this->vertex[i].x * rotationMatrix.y + this->vertex[i].y * rotationMatrix.x;
            this->vertex[i] = tmp;
        }
        this->move(backup);

    };

    void zoom(double k)
    {
        Point axis = this->vertex[0];
        for (int i = 1; i < n; i++)
        {
            this->vertex[i].x = k * (this->vertex[i].x - axis.x) + axis.x;
            this->vertex[i].y = k * (this->vertex[i].y - axis.y) + axis.y;
		};
    };

	double oxPrLength() const
	{
		double xmin = vertex[0].x;
		double xmax = xmin;
		for (int i = 1; i < n; i++)
		{
			if (vertex[i].x < xmin) xmin = vertex[i].x;
			if (vertex[i].x > xmax) xmax = vertex[i].x;
		}
		return (xmax - xmin);
	};

	bool equalÎxProjectionLength(const Shape& c) const
	{
		return (this->oxPrLength() == c.oxPrLength());
	};

	std::ostream &print(std::ostream &output) const
	{
		output << std::endl << "#" << this->getId() << " Pentagon colour:  " << this->colour << std::endl << "Vertices: ";
		for (int i = 0; i < n; i++)
		{
			output << "(" << this->vertex[i].x << ", " << this->vertex[i].y << ")   ";
		}
		output << std::endl << std::endl;
		return output;
	}

   /* friend std::ostream &operator<<(std::ostream &output, const Shape &p)
    {
        return p.print(output);
    };*/
};

#endif
