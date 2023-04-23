// Example program
#include <iostream>

typedef struct Color {
	unsigned char r;
	unsigned char g;
	unsigned char b;

	Color(unsigned char red = 0, unsigned char green = 0, unsigned char blue = 0) :
		r(red), 
		g(green), 
		b(blue)
	{
	}

	Color(const Color& other) : 
		r(other.r), 
		b(other.b), 
		g(other.g) 
	{
	}

	friend inline std::ostream& operator<<(std::ostream& stream, const Color& color) {
		stream << '(' << (int)color.r << ',' << (int)color.g << ',' << (int)color.b << ')';
		return stream;
	}

} Color;

class Shape abstract{
public:

	void setCoordinates(double newX, double newY) {
		s_x = newX;
		s_y = newY;
	}

	Shape(double xCoordinate = 0.0, double yCoordinate = 0.0, double r_angle = 0.0, const Color& color = Color()) :
		s_x(xCoordinate), 
		s_y(yCoordinate), 
		s_color(color),
		rotation_angle(r_angle),
		_id (_id_counter++)
	{
	}

	~Shape() = default;

	void setColor(const Color& newColor)
	{
		s_color = newColor;
	}

	const Color getColor() const noexcept{
		return s_color;
	}

	void rotate(double angle) {
		rotation_angle += angle;
	}

	virtual void scale(double) = 0;

	friend inline std::ostream& operator<<(std::ostream& stream, Shape& shape) {
		return shape.printShape(stream);
	}

	const size_t get_id() const noexcept{
		return _id;
	}

protected:
	virtual std::ostream& printShape(std::ostream&) = 0;
	const size_t _id;
	double s_x;
	double s_y;
	double rotation_angle;
	Color s_color;
private:
	static size_t _id_counter;
};

size_t Shape::_id_counter = 0;

class Sector : public Shape {
public:
	Sector(double x = 0, double y = 0, double r_angle = 0.0, Color color = Color(), double radius = 1.0, double angle = 360.0) :
		Shape(x, y, r_angle, color), 
		s_radius(radius),
		s_angle(angle)
	{
	}

	Sector(const Sector& other):
		Shape(other.s_x, other.s_y, other.rotation_angle, other.s_color),
		s_angle(other.s_angle),
		s_radius(other.s_radius)
	{
	}

	Sector& operator=(Sector& other) {
		s_angle = other.s_angle;
		s_color = other.s_color;
		rotation_angle = other.rotation_angle;
		s_x = other.s_x;
		s_y = other.s_y;
		return *this;
	}

	void scale(double coefficient) override {
		s_radius *= coefficient;
	}

	~Sector() = default;

private:
	std::ostream& printShape(std::ostream& stream = std::cout) override{
		stream << "Sector of " << s_angle << " degrees of a circle with radius " << s_radius << " on position (" << this->s_x << ',' << this->s_y << ")" << " rotated by " << this->rotation_angle << " degrees" << ". Shape's color is " << this->s_color << " id - " << get_id() << std::endl;
		return stream;
	}

	double s_angle;
	double s_radius;
};

class Parallelogram : public Shape {
public:
	Parallelogram(double x = 0, double y = 0, double r_angle = 0.0, Color color = Color(), double leg1 = 1.0, double leg2 = 1.0, double angle = 90.0) :
		Shape(x, y, r_angle, color),
		p_leg1(leg1),
		p_leg2(leg2),
		p_angle(angle)
	{
	}

	Parallelogram(const Parallelogram& other) :
		Shape(other.s_x, other.s_y, other.rotation_angle, other.s_color),
		p_leg1(other.p_leg1),
		p_leg2(other.p_leg2),
		p_angle(other.p_angle)
	{
	}

	Parallelogram& operator=(Parallelogram& other) {
		p_leg1 = other.p_leg1;
		p_leg2 = other.p_leg2;
		p_angle = other.p_angle;
		s_color = other.s_color;
		rotation_angle = other.rotation_angle;
		s_x = other.s_x;
		s_y = other.s_y;
		return *this;
	}

	void scale(double coefficient) override {
		p_leg1 *= coefficient;
		p_leg2 *= coefficient;
	}

	~Parallelogram() = default;

private:
	std::ostream& printShape(std::ostream& stream = std::cout) override {
		stream << "Parallelogram with legs " << p_leg1 << " and " << p_leg2 << " with base angle of " << p_angle << " degrees on position (" << this->s_x << "," << this->s_y << ")" << " rotated by " << this->rotation_angle << " degrees" << ". Shape's color is " << this->s_color << " id - " << get_id() << std::endl;
		return stream;
	}

	double p_leg1;
	double p_leg2;
	double p_angle;
};

class Ellipse : public Shape {
public:
	Ellipse(double x = 0, double y = 0, double r_angle = 0.0, const Color& color = Color(), double a = 1.0, double b = 1.0) :
		Shape(x, y, r_angle, color),
		e_a(a),
		e_b(b)
	{
	}

	Ellipse(const Ellipse& other) :
		Shape(other.s_x, other.s_y, other.rotation_angle, other.s_color),
		e_a(other.e_a),
		e_b(other.e_b)
	{
		rotation_angle = other.rotation_angle;
	}

	Ellipse& operator=(Ellipse& other) {
		e_a = other.e_a;
		e_b = other.e_b;
		rotation_angle = other.rotation_angle;
		s_x = other.s_x;
		s_y = other.s_y;
		return *this;
	}

	void scale(double coefficient) override {
		e_a *= coefficient;
		e_b *= coefficient;
	}

	~Ellipse() = default;

private:
	std::ostream& printShape(std::ostream& stream = std::cout) override {
		stream << "Ellipse with parameters " << e_a << " and " << e_b << " on position (" << this->s_x << "," << this->s_y << ")" << " rotated by " << this->rotation_angle << " degrees" << ". Shape's color is " << this->s_color << " id - " << get_id() << std::endl;
		return stream;
	}

	double e_a;
	double e_b;
};

int main()
{
	Sector s(2, 4, 5, Color(12, 15, 64), 5, 45);
	Sector b;
	b = s;
	b.rotate(45);
	b.scale(0.5);
	b.setColor(Color(0, 0, 0));

	Parallelogram p(45, 54, 0, Color(0,0,0), 5, 5, 90);

	Ellipse e(11, 12, 90, Color(2, 255, 16), 10, 10);
	
	std::cout << s << p << e << b;

	system("pause");
    return 0;
}