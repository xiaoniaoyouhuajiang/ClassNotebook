#include "figures.h"

Pentagon::Pentagon(double x, double y, int SideSize) : Shape(x, y), side(SideSize)
{
	points.clear();
	double R = SideSize / sqrt(2 - 2 * cos(180 / 5));
	double rotor = 0;
	Point tmp;

	for (int i = 1; i < (5 * 2 + 1); i++)
	{
		if (i % 2)
		{
			tmp.Set_X(x + R * cos(rotor * M_PI / 180));
			tmp.Set_Y(y - R * sin(rotor * M_PI / 180));
			points.push_back(tmp);
		}
		rotor += 180 / 5;
	}
	SetPerimetr();
}

void Pentagon::ChangeCoordinates(double new_x, double new_y) {
	Point tmp(x - new_x, y - new_y);

	x = new_x;
	y = new_y;

	for (auto& p : points) {
		p = p + tmp;
	}
}

void Pentagon::Rotate(double new_angle)
{
	if (new_angle == 360 || new_angle == 0) {
		return;
	}

	angle += new_angle;
	angle = fmod(angle, 360);

	double rot = (new_angle * M_PI) / 180;
	double tmp_X = 0;
	double tmp_Y = 0;
	for (auto& p : points) {
		tmp_X = x + (p.Get_X() - x) * cos(rot) - (p.Get_Y() - y) * sin(rot);
		tmp_Y = y + (p.Get_X() - x) * sin(rot) + (p.Get_Y() - y) * cos(rot);
		p.Set_X(tmp_X);
		p.Set_Y(tmp_Y);
	}
}

void Pentagon::Scale(double factor)
{
	x *= factor;
	y *= factor;
	for (auto& p : points) {
		p.Set_X(p.Get_X() * factor);
		p.Set_Y(p.Get_Y() * factor);
	}
}

void Pentagon::SetColour(int r, int g, int b)
{
	RGB.SetColour(r, g, b);
}

Colour Pentagon::GetColour()
{
	return RGB;
}

int Pentagon::GetSide() {
	return side;
}

Point Pentagon::GetCenter() const {
	return Point(x, y);
}

void Pentagon::SetPerimetr() {
	perimetr = 5 * side;
}

double Pentagon::GetPerimetr() const
{
	return perimetr;
}

ostream& Pentagon::operator<<(ostream& stream) const
{
	stream.setf(ios::right | ios::fixed);
	stream << "PENTAGON" << endl << "Center: " << x << ", " << y << endl
		<< "Angle: " << angle << endl
		<< "Colour: " << RGB << "Perimetr: " << perimetr << endl;
	stream << "Points: " << "1. " << points[0] << endl;
	if (points.size() > 0) {
		for (unsigned int i = 1; i < points.size(); ++i) {
			stream << setw(9) << i + 1 << ". " << points[i] << endl;
			if (i + 1 == points.size()) {
				stream << endl;
				break;
			}
		}
	}
	return stream;
}

Pentagram::Pentagram(double x, double y, double Radius) : Shape(x, y), radius(Radius)
{
	points.clear();
	PentVertex top_vertex = PentVertex(0, Radius);
	double angle = arg(top_vertex) * 4.0 / 5.0;
	PentVertex del = polar(1.0, angle);
	PentVertex center = PentVertex(x, y);
	PentVertex current_vertex = top_vertex;
	for (int i = 0; i < 5; ++i) {
		points.push_back(Point((current_vertex + center).real(), (current_vertex + center).imag()));
		current_vertex /= del;
	}
	SetPerimetr();
}

void Pentagram::ChangeCoordinates(double new_x, double new_y) {
	Point tmp(x - new_x, y - new_y);

	x = new_x;
	y = new_y;

	for (auto& p : points) {
		p = p + tmp;
	}
}

void Pentagram::Rotate(double new_angle)
{
	if (new_angle == 360 || new_angle == 0) {
		return;
	}

	angle += new_angle;
	angle = fmod(angle, 360);

	double rot = (new_angle * M_PI) / 180;
	double tmp_X = 0;
	double tmp_Y = 0;
	for (auto& p : points) {
		tmp_X = x + (p.Get_X() - x) * cos(rot) - (p.Get_Y() - y) * sin(rot);
		tmp_Y = y + (p.Get_X() - x) * sin(rot) + (p.Get_Y() - y) * cos(rot);
		p.Set_X(tmp_X);
		p.Set_Y(tmp_Y);
	}
}

void Pentagram::Scale(double factor)
{
	x *= factor;
	y *= factor;
	radius *= factor;
	for (auto& p : points) {
		p.Set_X(p.Get_X() * factor);
		p.Set_Y(p.Get_Y() * factor);
	}
}

void Pentagram::SetColour(int r, int g, int b)
{
	RGB.SetColour(r, g, b);
}

Colour Pentagram::GetColour()
{
	return RGB;
}

double Pentagram::GetRadius()
{
	return radius;
}

Point Pentagram::GetCenter() const {
	return Point(x, y);
}

void Pentagram::SetPerimetr()
{
	double side = radius * tan(0.628319);
	perimetr = 10 * side;
}

double Pentagram::GetPerimetr() const
{
	return perimetr;
}

ostream& Pentagram::operator<<(ostream& stream) const
{
	stream.setf(ios::right | ios::fixed);
	stream << "PENTAGRAM" << endl << "Center: " << x << ", " << y << endl
		<< "Angle: " << angle << endl
		<< "Colour: " << RGB << "Perimetr: " << perimetr << endl;
	stream << "Points: " << "1. " << points[0] << endl;
	if (points.size() > 0) {
		for (unsigned int i = 1; i < points.size(); ++i) {
			stream << setw(9) << i + 1 << ". " << points[i] << endl;
			if (i + 1 == points.size()) {
				stream << endl;
				break;
			}
		}
	}
	return stream;
}

Rectangle::Rectangle(double x, double y, double _length, double _width) : Shape(x, y), length(_length), width(_width)
{
	points.clear();
	points.push_back({ x - (length / 2), y - (width / 2) });
	points.push_back({ x - (length / 2), y + (width / 2) });
	points.push_back({ x + (length / 2), y + (width / 2) });
	points.push_back({ x + (length / 2), y - (width / 2) });
	SetPerimetr();
}

void Rectangle::ChangeCoordinates(double new_x, double new_y) {
	Point tmp(x - new_x, y - new_y);

	x = new_x;
	y = new_y;

	for (auto& p : points) {
		p = p + tmp;
	}
}

void Rectangle::Rotate(double new_angle)
{
	if (new_angle == 360 || new_angle == 0) {
		return;
	}

	angle += new_angle;
	angle = fmod(angle, 360);

	double rot = (new_angle * M_PI) / 180;
	double tmp_X = 0;
	double tmp_Y = 0;
	for (auto& p : points) {
		tmp_X = x + (p.Get_X() - x) * cos(rot) - (p.Get_Y() - y) * sin(rot);
		tmp_Y = y + (p.Get_X() - x) * sin(rot) + (p.Get_Y() - y) * cos(rot);
		p.Set_X(tmp_X);
		p.Set_Y(tmp_Y);
	}
}

void Rectangle::Scale(double factor)
{
	x *= factor;
	y *= factor;
	length *= factor;
	width *= factor;
	for (auto& p : points) {
		p.Set_X(p.Get_X() * factor);
		p.Set_Y(p.Get_Y() * factor);
	}
}

void Rectangle::SetColour(int r, int g, int b)
{
	RGB.SetColour(r, g, b);
}

Colour Rectangle::GetColour()
{
	return RGB;
}

Point Rectangle::GetCenter() const {
	return Point(x, y);
}


double Rectangle::GetLength()
{
	return length;
}

double Rectangle::GetWidth()
{
	return width;
}

void Rectangle::SetPerimetr()
{	
	perimetr = 2 * (length + width);
}

double Rectangle::GetPerimetr() const
{
	return perimetr;
}

ostream& Rectangle::operator<<(ostream& stream) const
{
	stream.setf(ios::right | ios::fixed);
	stream << "RECTANGLE" << endl << "Center: " << x << ", " << y << endl
		<< "Angle: " << angle << endl
		<< "Colour: " << RGB << "Perimetr: " << perimetr << endl;
	stream << "Points: " << "1. " << points[0] << endl;
	if (points.size() > 0) {
		for (unsigned int i = 1; i < points.size(); ++i) {
			stream << setw(9) << i + 1 << ". " << points[i] << endl;
			if (i + 1 == points.size()) {
				stream << endl;
				break;
			}
		}
	}
	return stream;
}
