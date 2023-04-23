// Борисовский Д.Ю. 
// Лабораторная работа №2 ООП

// Индивидуальный вариант: Прямоугольник, квадрат, эллипс

// Индивидуальное задание: 
// "Добавить в класс Shape метод bool isInsideOfAnother(const Shape& other), который будет возвращать true, если фигура 
// находится внутри другого объекта (other), переданного в данный метод. Ну и false в противном случае.  Этот метод 
// должен быть покрыт модульными тестами google test."

#include "stdafx.h"
#include <iostream>
#define _USE_MATH_DEFINES 
#include <math.h>
#include <map>
#include "gtest/gtest.h"

using namespace std;

//цвет фигуры
enum color_type { red, orange, yellow, green, blue, violet, white, black };

map <color_type, char*> map_of_colour = {
	{ red, "Red" },
	{ orange, "Orange" },
	{ yellow, "Yellow" },
	{ green, "Green" },
	{ blue, "Blue" },
	{ violet, "Violet" },
	{ white, "White" },
	{ black, "Black" }
};

struct Point
{
	Point() : x(0.0), y(0.0) {}
	Point(double x, double y) : x(x), y(y) {}
	friend Point operator- (const Point& left, const Point& right)
	{
		return Point(left.x - right.x, left.y - right.y);
	}
	friend Point operator+ (const Point& left, const Point& right)
	{
		return Point(left.x + right.x, left.y + right.y);
	}
	friend Point operator* (const Point& left, double parametr)
	{
		return Point(left.x * parametr, left.y * parametr);
	}
	double x;
	double y;
};

double length(const Point &left, const Point &right)
{
	return sqrt(pow((left.x - right.x), 2) + pow((left.y - right.y), 2));
}

Point rotate_point(const Point &point, const Point &relative, const double &angle)
{
	Point result = point;
	result = result - relative;
	double x_help = result.x;
	result.x = (x_help * cos(angle)) - (result.y * sin(angle));
	result.y = (x_help * sin(angle)) + (result.y * cos(angle));
	result = result + relative;
	return result;
}

float square_triangle(const Point& first, const Point& second, const Point& third)
{
	float a = length(first, second);
	float b = length(second, third);
	float c = length(third, first);
	float p = (a + b + c) / 2;
	return sqrt(p*(p - a)*(p - b)*(p - c));
}

float my_round(float argument)
{
	return roundf(argument * 10000) / 10000;
}

class Shape
{
protected:
	Point center;
	Point vertex[4];
	color_type color = white;
	unsigned ID;
public:
	void move(const Point &z)
	{
		Point reserv;
		reserv = z - this->center;
		this->center = z;
		for (auto&& i : this->vertex)
		{
			i = i + reserv;
		}
	}

	void rotate(double angle)
	{
		for (auto&& i : this->vertex)	i = rotate_point(i, this->center, angle);
	}

	void zoom(double arg = 1.0)
	{
		Point reserv = center;
		this->move(Point(0, 0));
		for (auto&& i : this->vertex)	i = i * arg;
		this->move(reserv);
	}

	void set_color(color_type parametr) { color = parametr; }

	color_type get_color() const { return color; }

	friend ostream& operator<< (ostream &out, Shape const& obj)
	{
		obj.show();
		out << "Point A - (" << obj.vertex[0].x << ',' << obj.vertex[0].y << ") \n";
		out << "Point B - (" << obj.vertex[1].x << ',' << obj.vertex[1].y << ") \n";
		out << "Point C - (" << obj.vertex[2].x << ',' << obj.vertex[2].y << ") \n";
		out << "Point D - (" << obj.vertex[3].x << ',' << obj.vertex[3].y << ") \n";
		out << "Center - (" << obj.center.x << ',' << obj.center.y << ") \n";
		out << "Color - " << map_of_colour[obj.color] << endl;
		out << "ID - " << obj.get_ID() << endl;
		out << endl << endl;
		return out;
	}

	void set_ID()
	{
		static unsigned counter = 0;
		ID = ++counter;
	}

	unsigned get_ID() const { return ID; }

	virtual float square() const = 0;

	virtual void show() const = 0;

	bool isInsideOfAnother(const Shape& other) const
	{
		for (auto&& i : this->vertex) if (!other.isPointInside(i)) return false;
		return true;
	}

	virtual bool isPointInside(const Point& point) const = 0;

	virtual ~Shape() {}
};

class Rectangle : public Shape
{
public:
	Rectangle(const Point &center, const Point &first_vertex, const Point &second_vertex)
	{
		//если длины полудиагоналей не равны или заданные вершины димаетрально противоположны
		if (((second_vertex.x == first_vertex.x + 2 * abs(first_vertex.x - center.x)) &&
			(second_vertex.y == first_vertex.y + 2 * abs(first_vertex.y - center.y))) ||
			(length(first_vertex, center) != length(second_vertex, center)))
			throw invalid_argument("The lengths of the half-diagonals are not equal" 
									"or the given vertices are dimaetrically opposite");
		this->center = center;
		this->vertex[0] = first_vertex;
		this->vertex[1] = second_vertex;
		this->vertex[2] = rotate_point(first_vertex, center, M_PI);
		this->vertex[3] = rotate_point(second_vertex, center, M_PI);
		set_ID();
	}

	Rectangle(const Point &center, const Point &first_vertex, const Point &second_vertex, color_type color)
		:Rectangle(center, first_vertex, second_vertex) {
		this->color = color;
	}

	float square() const override
	{
		return length(vertex[0], vertex[1]) * length(vertex[1], vertex[2]);
	}

	void show() const override
	{
		cout << "Rectangle\n";
	}

	bool isPointInside(const Point& point) const override
	{
		//если сумма площадей четрыех треугольников, образованных с помощью всех вершин прямоугольника
		//и заданной точки равна площади прямоугольника, то точка находится внутри фигуры
		if (my_round(square_triangle(vertex[0], vertex[1], point) )
			+ my_round(square_triangle(vertex[1], vertex[2], point)) 
			+ my_round(square_triangle(vertex[2], vertex[3], point)) 
			+ my_round(square_triangle(vertex[3], vertex[0], point)) 
			!= my_round(square() ) )   return false;
		else return true;
	}
};

class Ellipse : public Shape
{
public:
	Ellipse(const Point &center, const Point &first_vertex, const Point &second_vertex)
	{
		//Если угол между полуосями не равен 90 градусов
		if ((static_cast <float> (pow(length(first_vertex, center), 2)) + static_cast <float> (pow(length(second_vertex, center), 2))) 
			!= static_cast <float> (pow(length(first_vertex, second_vertex), 2)))
			throw invalid_argument("The angle between the semiaxes is not equal to 90 degrees");

		this->center = center;
		this->vertex[0] = first_vertex;
		this->vertex[1] = second_vertex;
		this->vertex[2] = rotate_point(first_vertex, center, M_PI);
		this->vertex[3] = rotate_point(second_vertex, center, M_PI);
		set_ID();
	}
	Ellipse(const Point &center, const Point &first_vertex, const Point &second_vertex, color_type color)
		:Ellipse(center, first_vertex, second_vertex)
	{
		this->color = color;
	}

	void show() const override
	{
		cout << "Ellipse\n";
	}

	float square() const override
	{
		return length(center, vertex[0]) * length(center, vertex[1]) * M_PI;
	}

	bool isPointInside(const Point& point) const override
	{
		//сохранение текущих координат центра и перемещение в начало координат для поворота
		Ellipse help_ellipse = *this;

		Point reserv = help_ellipse.center;
		help_ellipse.move(Point(0, 0));

		//получение индекса одной из точек пересечения большей оси с эллипсом
		int index = length(help_ellipse.center, help_ellipse.vertex[0]) > length(help_ellipse.center, help_ellipse.vertex[1]) ? 0 : 1;

		//вычисление угла между главной полуосью и осью ОХ
		float a = length(help_ellipse.center, help_ellipse.vertex[index]);
		Point help(abs(help_ellipse.vertex[index].x), 0);
		float b = length(help_ellipse.center, help);
		float angle = acos(b / a);

		//поворот эллипса так, чтобы главная ось совпадала с осью ОХ
		if (((help_ellipse.vertex[index].y > help.y) && (help_ellipse.vertex[index].x > help.x))
			|| ((help_ellipse.vertex[index].y < help.y) && (help_ellipse.vertex[index].x < help.x)))
		{
			help_ellipse.rotate(-angle);
		}
		else
		{
			help_ellipse.rotate(angle);
			angle = -angle;
		}

		//вычисление длины болшей оси эллипса (суммы расстояний от фокусов до эллипса)
		double distance = length(help_ellipse.vertex[index], help_ellipse.vertex[index + 2]);

		//вычисление квадратов длин главной и побочной полуосей эллипса a^2 и b^2
		//(для того, чтобы найти расстояние до фокусов по формуле c = sqrt(a^2-b^2) )

		double maximum = pow(length(help_ellipse.center, help_ellipse.vertex[index]), 2);
		double minimum = pow(length(help_ellipse.center, help_ellipse.vertex[index + 1]), 2);
		double focus_length = sqrt(maximum - minimum);

		//вычисление координат фокусов
		Point first_focus(focus_length, 0);
		Point second_focus(-focus_length, 0);


		//возвращение вычисленных фокусов на прежнее состояние 

		//поворот
		first_focus = rotate_point(first_focus, help_ellipse.center, angle);
		second_focus = rotate_point(second_focus, help_ellipse.center, angle);


		//перемещение
		first_focus = first_focus + reserv;
		second_focus = second_focus + reserv;

		//проверка нахождения точки внутри эллипса 
		if (my_round(length(first_focus, point))  + my_round(length(second_focus, point)) 
			> my_round (distance) ) return false;
		else return true;
	}
};

class Square : public Shape
{
public:
	Square(const Point &center, const Point &vertex)
	{
		this->center = center;
		this->vertex[0] = vertex;
		for (size_t i = 1; i<4; ++i)	this->vertex[i] = rotate_point(this->vertex[i - 1], center, M_PI / 2);
		set_ID();
	}
	Square(const Point &center, const Point &vertex, color_type color) : Square(center, vertex) { this->color = color; }

	void show() const override
	{
		cout << "Square\n";
	}

	float square() const override
	{
		return length(vertex[0], vertex[1]) * length(vertex[1], vertex[2]);
	}

	bool isPointInside(const Point& point) const override
	{
		//если расстояние от центра квадрата до точки больше половины длины полудиагонали, то точка не попала
		if (length(center, point) > length(center, vertex[0])) return false;
		else return true;
	}
};

TEST(Figure_Tests, Square_in_Ellipse_True)
{
	Square square(Point(3, 3), Point(2, 2));
	Ellipse ellipse(Point(3, 3), Point(3, 1), Point(1, 3));
	EXPECT_EQ(true, square.isInsideOfAnother(ellipse));
}

TEST(Figure_Tests, Square_in_Ellipse_False)
{
	Square square(Point(3, 3), Point(1, 1));
	Ellipse ellipse(Point(3, 3), Point(3, 1), Point(1, 3));
	EXPECT_EQ(false, square.isInsideOfAnother(ellipse));
}

TEST(Figure_Tests, Square_in_Rectangle_True)
{
	Square square(Point(3, 3), Point(2, 2));
	Rectangle rectangle(Point(2, 3), Point(0, 0), Point(0, 6));
	EXPECT_EQ(true, square.isInsideOfAnother(rectangle));
}

TEST(Figure_Tests, Square_in_Rectangle_False)
{
	Square square(Point(3, 3), Point(2, 2));
	Rectangle rectangle(Point(1.5, 3), Point(0, 0), Point(0, 6));
	EXPECT_EQ(false, square.isInsideOfAnother(rectangle));
}

TEST(Figure_Tests, Square_in_Square_True)
{
	Square square(Point(3, 3), Point(2, 2));
	Square square_other(Point(3, 3), Point(3, 1));
	EXPECT_EQ(true, square.isInsideOfAnother(square_other));
}

TEST(Figure_Tests, Square_in_Square_False)
{
	Square square(Point(3, 3), Point(2, 2));
	Square square_other(Point(3, 3), Point(3, 2));
	EXPECT_EQ(false, square.isInsideOfAnother(square_other));
}

TEST(Figure_Tests, Ellipse_in_Square_True)
{
	Ellipse ellipse(Point(3, 3), Point(1, 1), Point(2, 4));
	Square square(Point(3, 3), Point(1, 1));
	EXPECT_EQ(true, ellipse.isInsideOfAnother(square));
}

TEST(Figure_Tests, Ellipse_in_Square_False)
{
	Ellipse ellipse(Point(3, 3), Point(1, 1), Point(2, 4));
	Square square(Point(3, 3), Point(2, 2));
	EXPECT_EQ(false, ellipse.isInsideOfAnother(square));
}

TEST(Figure_Tests, Ellipse_in_Rectangle_True)
{
	Ellipse ellipse(Point(3, 3), Point(1, 1), Point(2, 4));
	Rectangle rectangle(Point(3, 3.5), Point(1, 0), Point(1, 7));
	EXPECT_EQ(true, ellipse.isInsideOfAnother(rectangle));
}

TEST(Figure_Tests, Ellipse_in_Rectangle_False)
{
	Ellipse ellipse(Point(3, 3), Point(1, 1), Point(2, 4));
	Rectangle rectangle(Point(3, 3), Point(3, 1), Point(1, 3));
	EXPECT_EQ(false, ellipse.isInsideOfAnother(rectangle));
}

TEST(Figure_Tests, Ellipse_in_Ellipse_True)
{
	Ellipse ellipse(Point(3, 3), Point(1, 1), Point(2, 4));
	Ellipse ellipse_other(Point(3, 3), Point(0, 0), Point(1, 5));
	EXPECT_EQ(true, ellipse.isInsideOfAnother(ellipse_other));
}

TEST(Figure_Tests, Ellipse_in_Ellipse_False)
{
	Ellipse ellipse(Point(3, 3), Point(1, 1), Point(2, 4));
	Ellipse ellipse_other(Point(3, 3), Point(5, 1), Point(2, 2));
	EXPECT_EQ(false, ellipse.isInsideOfAnother(ellipse_other));
}

TEST(Figure_Tests, Rectangle_in_Ellipse_True)
{
	Rectangle rectangle(Point(3, 3), Point(2, 1), Point(4, 1));
	Ellipse ellipse(Point(3, 3), Point(0, 6), Point(1, 1));
	EXPECT_EQ(true, rectangle.isInsideOfAnother(ellipse));
}

TEST(Figure_Tests, Rectangle_in_Ellipse_False)
{
	Rectangle rectangle(Point(3, 3), Point(2, 1), Point(4, 1));
	Ellipse ellipse(Point(3, 3), Point(4, 4), Point(5, 1));
	EXPECT_EQ(false, rectangle.isInsideOfAnother(ellipse));
}

TEST(Figure_Tests, Rectangle_in_Square_True)
{
	Rectangle rectangle(Point(3, 3), Point(2, 1), Point(4, 1));
	Square square(Point(3, 3), Point(1, 1));
	EXPECT_EQ(true, rectangle.isInsideOfAnother(square));
}

TEST(Figure_Tests, Rectangle_in_Square_False)
{
	Rectangle rectangle(Point(3, 3), Point(2, 1), Point(4, 1));
	Square square(Point(3, 3), Point(3, 1));
	EXPECT_EQ(false, rectangle.isInsideOfAnother(square));
}

TEST(Figure_Tests, Rectangle_in_Rectangle_True)
{
	Rectangle rectangle(Point(3, 3), Point(2, 1), Point(4, 1));
	Rectangle rectangle_other(Point(3, 3), Point(2, 1), Point(4, 1));
	EXPECT_EQ(true, rectangle.isInsideOfAnother(rectangle_other));
}

TEST(Figure_Tests, Rectangle_in_Rectangle_False)
{
	Rectangle rectangle(Point(3, 3), Point(2, 1), Point(4, 1));
	Rectangle rectangle_other(Point(3, 3), Point(2, 2), Point(2, 4));
	EXPECT_EQ(false, rectangle.isInsideOfAnother(rectangle_other));
}

GTEST_API_ int main(int argc, char **argv) {

	setlocale(0, "Rus");
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("pause");
	return 0;
}