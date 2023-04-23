#pragma once
#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED

#include <string>
#include <iostream>
#include <cassert>
#include <cstdlib>



const double PI = 3.1415926535897932384626433832795;

struct Point
{
    double x, y;
    Point &operator+=(const Point &p)
    {
        this->x += p.x;
        this->y += p.y;
        return *this;
    };
};

class Shape
{
protected:
    std::string colour;
    unsigned int id;

private:
    unsigned int asignId()
    {
        static unsigned int counter = 0;
        counter++;
        return counter;
    };

public:
	static const std::string ofColours[];// = { "red", "green", "blue", "yellow", "black", "purple", "orange", "white", "gray" }; // 0 : 8

    unsigned int getId() const
    {
        return id;
    };

    Shape(const std::string &colour)
    {
        this->colour = colour;
        id = asignId();
    };

    virtual void move(Point destination) = 0;
    virtual void rotate(double angle) = 0;
    virtual void zoom(double k) = 0;
	virtual bool equalÎxProjectionLength(const Shape& other) const = 0;
	/*{
		if (other.oxPrLength() > 0) return false;
		return true;
	};*/

	virtual double oxPrLength() const = 0;
	/*{
		return 0;
	};*/

    void setColour(const std::string &colour)
    {
        this->colour = colour;
    };

    std::string getColour() const
    {
        return this->colour;
    };

	virtual std::ostream& print(std::ostream& output) const = 0;

	friend std::ostream &operator<<(std::ostream &output, const Shape &c)
	{
		return c.print(output);
	};


    /*friend std::ostream &operator<<(std::ostream &output, const Shape &s)
    {
        output << "Shape colour:  " << s.colour << std::endl;
        return output;
    };*/
};




Point dif(Point initial, Point terminal)
{
    Point p;
    p.x = terminal.x - initial.x;
    p.y = terminal.y - initial.y;
    return p;
};


const std::string Shape::ofColours[] = { "red", "green", "blue", "yellow", "black", "purple", "orange", "white", "gray" }; // 0 : 8


#endif // SHAPE_HPP_INCLUDED
