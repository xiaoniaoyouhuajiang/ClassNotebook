#ifndef OOP_LR2
#define OOP_LR2
#include <iostream>
#include <vector>
#include <cmath>

unsigned getNumberDigits(unsigned x);

class Point
{
public:
	float x;
	float y;
	Point(float x_, float y_);
	void move(float x_, float y_);
	void rotate(float alpha);
	void scale(Point point0, float k);
};
 
class Shape
{
private:
	unsigned color;	
protected:
	std::vector<Point> point;
public:
	Shape();
	virtual ~Shape() {};
	void Move(float x_, float y_);  
	void Rotate(float alpha);
	void setColor(unsigned color_);
	unsigned getColor() const;
	virtual void Scale(float k) = 0;
	virtual std::ostream& put(std::ostream& out) const = 0;
	friend std::ostream& operator<< (std::ostream& s, const Shape& shape_);
	virtual unsigned getId() = 0;
	virtual float Perimeter() = 0;
};

class Ellipse : public Shape
{
private:
	float r1;
	float r2;
	static unsigned next_id_ellipse;
	unsigned id_ellipse;
public:
	Ellipse(Point center, float r1_, float r2_);
	unsigned getId();
	void Scale(float k);
	std::ostream& put(std::ostream& out) const;
	float Perimeter();
};

class Trapezium : public Shape
{
private:
	static unsigned next_id_trapezium;	
	unsigned id_trapezium;	
	virtual std::string FriendlyName() const;
protected:
	float topBase;
	float bottomBase;
public:
	Trapezium(Point topLeftCoord, Point bottomLeftCoord, float topBase_, float bottomBase_);
	unsigned getId();
	void Scale(float k);
	std::ostream& put(std::ostream& out) const;
	float Perimeter();
};

class IsoscelesTrapezium : public Trapezium
{
private:
	static unsigned next_id_isosceles;
	unsigned id_isosceles;
	std::string FriendlyName() const;		
public:
	IsoscelesTrapezium(Point topLeftCoord, Point bottomLeftCoord, float bottomBase);
	unsigned getId();

};
#endif
