#include "Isosceles_Trapezium.h"

/*Isosceles_Trapezium::Isosceles_Trapezium(double x, double y, double height, double length_bot, double length_top, string color) :
	Trapezium(x, y, 0, height, length_bot, length_top, color) {}*/

Isosceles_Trapezium::Isosceles_Trapezium(double x, double y, double delta, double height, double length_bot, double length_top,
double edge, string color)
	: delta(delta), height(height), length_bot(length_bot), length_top(length_top), edge(edge)
{
	this->centre.setX(x);
	this->centre.setY(y);
	this->color = color;
	vertex.push_back(Point(centre.getX() - length_bot / 2, centre.getY() - height / 2));
	vertex.push_back(Point(centre.getX() - length_top / 2 + delta, centre.getY() + height / 2));
	vertex.push_back(Point(centre.getX() + length_top / 2 + delta, centre.getY() + height / 2));
	vertex.push_back(Point(centre.getX() + length_bot / 2, centre.getY() - height / 2));
}

ostream& operator << (ostream &out, Isosceles_Trapezium &is_tr)
{
	out << "Isosceles Trapezium: color(" << is_tr.color << "), centre (" << is_tr.centre.getX() << ", " << is_tr.centre.getY() << "), height(";
	out << is_tr.height << "), base_1(" << is_tr.length_bot << "), base_2(" << is_tr.length_top << "), edge: " 
	<< is_tr.edge << endl;
	return out;
}

void Isosceles_Trapezium::scale(double k)
{
	height *= k;
	length_bot *= k;
	length_top *= k;
	delta *= k;
	edge *= k;
	vertex[0].setX(vertex[0].getX() - length_bot / 2);
	vertex[0].setY(vertex[0].getY() - height / 2);
	vertex[0].setX(vertex[0].getX() - length_top / 2 + delta);
	vertex[0].setY(vertex[0].getY() + height / 2);
	vertex[0].setX(vertex[0].getX() + length_bot / 2 + delta);
	vertex[0].setY(vertex[0].getY() + height / 2);
	vertex[0].setX(vertex[0].getX() + length_bot / 2);
	vertex[0].setY(vertex[0].getY() - height / 2);
}

/*double Isosceles_Trapezium::get_edge()
{
	return edge;
}

void Isosceles_Trapezium::set_edge(double edge)
{
	this->edge = edge;
}*/