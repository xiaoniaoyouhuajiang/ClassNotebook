#include <iostream>
#include <cmath>

struct RGB
{
	int red;
	int green;
	int blue;
};

class Shape
{
private:
	static unsigned int ID_c;
protected:
	double centre_x;
	double centre_y;
	double angle;
	RGB color;
	double scale = 1.0;
	unsigned int ID;
public:
	Shape()
	: centre_x(0.0), centre_y(0.0), angle(0.0), color({0,0,0}), ID(ID_c)
	{
		ID_c++;
	}

	Shape(double x, double y, const RGB& set_color)
	: centre_x(x), centre_y(y), angle(0.0), color(set_color), ID(ID_c)
	{
		ID_c++;
	}

	//Перемещение
	void move(double x, double y)
	{
		centre_x = x;
		centre_y = y;
	}

	//Поворот
	void rotate(double plus_angle)
	{
		angle += plus_angle;
	}

	//Масштаб
	virtual void scaling(double scale) = 0;

	//Установ цвета
	void set_color(const RGB& set_color)
	{
		color = set_color;
	}

	//Получение цвета
	RGB& get_color()
	{
		return color;
	}

};

unsigned int Shape::ID_c = 0;

class Triangle : public Shape
{
protected:
	double a;
	double b;
	double c;
public:
	Triangle()
	: Shape(), a(0.0), b(0.0), c(0.0)
	{}

	Triangle(double x, double y, const RGB& color, double a, double b, double c)
	: Shape(x, y, color), a(a), b(b), c(c)
	{}

	void scaling(double scale) override
	{
		a *= scale;
		b *= scale;
		c *= scale;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Triangle& tri)
	{
		stream << "Figure : Triangle" << std::endl;
		stream << "ID : " << tri.ID << std::endl;
		stream << "Centre coordinates: (" << tri.centre_x << ", " << tri.centre_y << ")" << std::endl;
		stream << "Angle : " << tri.angle << std::endl;
		stream << "Color (RGB) : " << tri.color.red << ":" << tri.color.green << ":" << tri.color.blue << std::endl;
		stream << "Scale : " << tri.scale << std::endl;
		stream << "Side: : a - " << tri.a << ", b - " << tri.b << ", c - "<< tri.c << std::endl;
		return stream;
	}
};
class Right_Triangle : public Triangle
{
public:
	Right_Triangle()
	: Triangle()
	{}

	Right_Triangle(double x, double y, const RGB& color, double cat1, double cat2)
	: Triangle(x, y, color, cat1, cat2, sqrt(pow(cat1, 2) + pow(cat2, 2)))
	{}

	friend std::ostream& operator<<(std::ostream& stream, const Right_Triangle& tri)
	{
		stream << "Figure : Right Triangle" << std::endl;
		stream << "ID : " << tri.ID << std::endl;
		stream << "Centre coordinates: (" << tri.centre_x << ", " << tri.centre_y << ")" << std::endl;
		stream << "Angle : " << tri.angle << std::endl;
		stream << "Color (RGB) : " << tri.color.red << ":" << tri.color.green << ":" << tri.color.blue << std::endl;
		stream << "Scale : " << tri.scale << std::endl;
		stream << "Side: : cat1 - " << tri.a << ", cat2 - " << tri.b << ", hyp - "<< tri.c << std::endl;
		return stream;
	}
};

class Ellipse : public Shape
{
protected:
	double a;
	double b;
public:
	Ellipse()
	: Shape(), a(0.0), b(0.0)
	{}

	Ellipse(double x, double y, const RGB& color, double m_a, double m_b)
	: Shape(x, y, color), a(m_a), b(m_b)
	{}

	void scaling(double scale)
	{
		a *= scale;
		b *= scale;
	}

	friend std::ostream& operator<<(std::ostream& stream, const Ellipse& el)
	{
		stream << "Figure : Ellipse" << std::endl;
		stream << "ID : " << el.ID << std::endl;
		stream << "Centre coordinates: (" << el.centre_x << ", " << el.centre_y << ")" << std::endl;
		stream << "Angle : " << el.angle << std::endl;
		stream << "Color (RGB) : " << el.color.red << ":" << el.color.green << ":" << el.color.blue << std::endl;
		stream << "Scale : " << el.scale << std::endl;
		stream << "Side: : a - " << el.a << ", b - " << el.b << std::endl;
		return stream;
	}

};

int main(){
	Triangle triangle(5, 10, {255, 0, 200}, 7, 2, 8);
	std::cout << "\033[4;32mDEMO TRIANGLE\033[0m" << std::endl;
	std::cout << triangle << std::endl;
	std::cout << "\033[4;32mROTATE TRIANGLE +50\033[0m" << std::endl;
	triangle.rotate(50);
	std::cout << triangle << std::endl;
	std::cout << "\033[4;32mSCALING TRIANGLE x25\033[0m" << std::endl;
	triangle.scaling(25);
	std::cout << triangle << std::endl;
	std::cout << "\033[4;32mSET COLOR TRIANGLE 80:80:80\033[0m" << std::endl;
	triangle.set_color({80, 80, 80});
	std::cout << triangle << std::endl;
	std::cout << "\033[4;32mMOVE TRIANGLE (50, 60)\033[0m" << std::endl;
	triangle.move(50, 60);
	std::cout << triangle << std::endl;

	Right_Triangle r_triangle(13, 13, {60, 60, 60}, 5 , 5);
	std::cout << "\033[4;36mDEMO RIGHT TRIANGLE\033[0m" << std::endl;
	std::cout << r_triangle << std::endl;

	Ellipse ellipse(4, 10, {40, 50, 60}, 3 , 8);
	std::cout << "\033[4;31mDEMO ELLIPSE\033[0m" << std::endl;
	std::cout << ellipse << std::endl;

	return 0;
}
