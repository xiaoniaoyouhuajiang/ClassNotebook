#include"polygon.h"
#include <algorithm>

Polygon::Polygon() : Shape(), tops() {}
Polygon::Polygon(const std::vector<Point> tops) : Shape(), tops(tops) {}
Polygon::Polygon(const std::vector<Point> tops, std::string red, std::string green, std::string blue) : Shape(red, green, blue) , tops(tops){}
Polygon::Polygon(const Polygon & other) : Shape(other), tops(other.tops) {}

Point Polygon::find_center() const									
{
	Point p(0, 0);
	for (size_t i = 0; i < tops.size(); i++)
		p += tops[i];
	p /= (double)tops.size();
	return p;
}

double Polygon::to_radian(double angle)
{
	return angle * PI / 180;
}

void Polygon::rotate(double angle)								
{
	Point center = find_center();	
	for (size_t i = 0; i < tops.size(); i++)				
		tops[i] -= center;
	for (size_t i = 0; i < tops.size(); i++)
		tops[i].rotate(to_radian(angle));							
	for (size_t i = 0; i < tops.size(); i++)				
		tops[i] += center;
}

void Polygon::scale(double coef)
{
	Point center = find_center();
	for (size_t i = 0; i < tops.size(); i++)
		tops[i] -= center;
	for (size_t i = 0; i < tops.size(); i++)
		tops[i].scale(coef);
	for (size_t i = 0; i < tops.size(); i++)
		tops[i] += center * coef;
}

void Polygon::move(const Point & p)
{
	for (size_t i = 0; i < tops.size(); i++)
		tops[i] += p;
}

void Polygon::out(std::ostream & out_) const
{
	out_ << "id: " << get_ID() << std::endl;
	out_ << "Colour: " << get_Colour() << std::endl;
	out_ << "Tops: ";
	for (size_t i = 0; i < tops.size(); i++)
		out_ << tops[i];
	out_ << std::endl;
	out_ << "Perimeter: " << perimeter() << std::endl;
	out_ << "Area: " << area() << std::endl;
}

void Polygon::swap(Polygon & other)
{
	colour = other.colour; 
	std::swap(tops, other.tops);
}
