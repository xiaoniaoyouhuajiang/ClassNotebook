#include "Trapezium.h"

/*Trapezium::Trapezium(double x, double y, double delta, double height, double length_bot, double length_top, string color)
	: delta(delta), height(height), length_bot(length_bot), length_top(length_top)
{
	this->centre.setX(x);
	this->centre.setY(y);
	this->color = color;
	vertex.push_back(Point(centre.getX() - length_bot / 2, centre.getY() - height / 2));
	vertex.push_back(Point(centre.getX() - length_top / 2 + delta, centre.getY() + height / 2));
	vertex.push_back(Point(centre.getX() + length_top / 2 + delta, centre.getY() + height / 2));
	vertex.push_back(Point(centre.getX() + length_bot / 2, centre.getY() - height / 2));
}*/

Trapezium::Trapezium(double x, double y, double delta, double height, double length_bot, double length_top, double edge, string color, double edge_2) :
Isosceles_Trapezium(x, y, delta, height, length_bot, length_top, edge, color), edge_2(edge_2)
{

}

void Trapezium::scale(double k)
{
	height *= k;
	length_bot *= k;
	length_top *= k;
	delta *= k;
	edge_2*=k;
	//double new_edge = get_edge();
	//set_edge(new_edge*k);
	edge*=k;
	vertex[0].setX(vertex[0].getX() - length_bot / 2);
	vertex[0].setY(vertex[0].getY() - height / 2);
	vertex[0].setX(vertex[0].getX() - length_top / 2 + delta);
	vertex[0].setY(vertex[0].getY() + height / 2);
	vertex[0].setX(vertex[0].getX() + length_bot / 2 + delta);
	vertex[0].setY(vertex[0].getY() + height / 2);
	vertex[0].setX(vertex[0].getX() + length_bot / 2);
	vertex[0].setY(vertex[0].getY() - height / 2);
}

ostream& operator << (ostream &out, Trapezium &tr)
{
	out << "Trapezium: color(" << tr.color << "), centre (" << tr.centre.getX() << ", " << tr.centre.getY() << "), height(";
	out << tr.height << "), base_1(" << tr.length_bot << "), base_2(" << tr.length_top << "), delta(" << tr.delta << "), edge_1:"
	<< tr.edge<<", edge_2:"<<tr.edge_2 << endl;
	return out;
}