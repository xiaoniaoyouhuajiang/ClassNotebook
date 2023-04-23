#include <iostream>
#include <vector>

#define PI 3.14159265359

using namespace std;

class Point {
	double x;
	double y;
public:
	Point(double x=0, double y=0) : x(x), y(y) {};
	double get_x() const {
		return x;
	}
	double get_y() const {
		return y;
	}
	void set_x(double x) {
		this->x = x;
	}
	void set_y(double y) {
		this->y = y;
	}
};

class Color {
	unsigned int red;
	unsigned int green;
	unsigned int blue;
public:
	Color(unsigned int red, unsigned int green, unsigned int blue) :red(red), green(green), blue(blue) {};
	unsigned int get_red() const {
		return red;
	}
	unsigned int get_green() const{
		return green;
	}
	unsigned int get_blue() const {
		return blue;
	}
};

class Shape {
protected:
	Color color;
	unsigned long int id;
	Point center;
	vector <Point> points;
public:
	Shape(Color color, Point center):color(color), center(center) {
		static long int i = 0;
		id = i;
		i++;
	}
	void set_color(Color color) {
		this->color = color;
	}

	Color get_color() const {
		return color;
	}

	unsigned long int get_id() const {
		return id;
	}

	void moving(Point p) {
		double offset_by_x = p.get_x() - center.get_x();
		double offset_by_y = p.get_y() - center.get_y();
		for (size_t i = 0; i < points.size(); i++) {
			double tmp_x = points[i].get_x() + offset_by_x;
			double tmp_y = points[i].get_y() + offset_by_y;
			points[i].set_x(tmp_x);
			points[i].set_y(tmp_y);
		}
		center = p;
	}

	 void rotation(double grade) {
		double grade_in_rad = grade*PI/180.0;
		for (size_t i = 0; i < points.size(); i++) {
			double x =center.get_x()+(points[i].get_x()-center.get_x())*cos(grade_in_rad)-(points[i].get_y()-center.get_y())*sin(grade_in_rad);
			double y = center.get_y() + (points[i].get_x() - center.get_x())*sin(grade_in_rad) + (points[i].get_y() - center.get_y())*cos(grade_in_rad); ;
			points[i].set_x(x);
			points[i].set_y(y);
		}
	}

	virtual void scaling(double coefficient)=0;

	virtual ostream& print_shape(ostream& stream, Shape& shape) = 0;
	friend ostream& operator << (ostream& stream, Shape& shape) {
		return shape.print_shape(stream, shape);
	}
	
};

class Square : public Shape {
	double length;
public:
	Square(double lenght, Color color, Point center) :Shape(color, center){
		this->length = length;
		points.push_back(Point(center.get_x() - lenght / 2, center.get_y() - lenght / 2));
		points.push_back(Point(center.get_x() - lenght / 2, center.get_y() + lenght / 2));
		points.push_back(Point(center.get_x() + lenght / 2, center.get_y() + lenght / 2));
		points.push_back(Point(center.get_x() + lenght / 2, center.get_y() - lenght / 2));
	}
	void scaling(double coefficient) override{
		double x;
		double y;
		for (size_t i = 0; i < points.size(); i++) {
			x = center.get_x()+(points[i].get_x() - center.get_x())*coefficient;
			y = center.get_y()+(points[i].get_y() - center.get_y())*coefficient;
			points[i].set_x(x);
			points[i].set_y(y);
		}
	}
	ostream& print_shape(ostream& stream, Shape& shape) override {
		stream << "Фигура: квадрат" << endl;
		stream << "id фигуры: " << shape.get_id() << endl;
		stream << "Координаты фигуры: " << endl;
		for (size_t i = 0; i < points.size(); i++) {
			stream << "(" << points[i].get_x() << ";" << points[i].get_y() << ")" << endl;
		}
		stream << "Цвет фигуры: " << shape.get_color().get_red() << " " << shape.get_color().get_green() << " " << shape.get_color().get_blue() << endl;
		stream << "_____________________________________" << endl;
		return stream;
	}
};

class Parallelogram :public Shape{
	Point p1;
	Point p2;
	Point p3;
public:
	Parallelogram(Color color, Point p1, Point p2, Point p3) :Shape(color, center) {
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
		points.push_back(p1);
		points.push_back(p2);
		points.push_back(p3);
		points.push_back(Point(points[0].get_x() + (points[2].get_x() - points[1].get_x()), points[2].get_y()-(points[1].get_y()-points[0].get_y())));
		center.set_x((points[0].get_x() + points[2].get_x())/2);
		center.set_y((points[0].get_y() + points[2].get_y())/2);
	}

	void scaling(double coefficient) override {
		double x;
		double y;
		for (size_t i = 0; i < points.size(); i++) {
			x = center.get_x() + (points[i].get_x() - center.get_x())*coefficient;
			y = center.get_y() + (points[i].get_y() - center.get_y())*coefficient;
			points[i].set_x(x);
			points[i].set_y(y);
		}
	}

	ostream& print_shape(ostream& stream, Shape& shape) override {
		stream << "Фигура: параллелограмм" << endl;
		stream << "id фигуры: " << shape.get_id() << endl;
		stream << "Центр фигуры: " << "(" << center.get_x() << ";" << center.get_y() << ")" << endl;
		stream << "Координаты фигуры: " << endl;
		for (size_t i = 0; i < points.size(); i++) {
			stream << "(" << points[i].get_x() << ";" << points[i].get_y() << ")" << endl;
		}
		stream << "Цвет фигуры: " << shape.get_color().get_red() << " " << shape.get_color().get_green() << " " << shape.get_color().get_blue() << endl;
		stream <<  "_____________________________________" << endl;
		return stream;
	}

};

class Rhombus : public Shape {
	double diagonal1;
	double diagonal2;
public:
	Rhombus(double diagonal1, double diagonal2, Point p1, Color color) :Shape(color, center) {
		this->diagonal1 = diagonal1;
		this->diagonal2 = diagonal2;
		double x = p1.get_x();
		double y = p1.get_y()+diagonal1;
		points.push_back(p1);
		points.push_back(Point(p1.get_x() - diagonal2 / 2, diagonal1 / 2));
		points.push_back(Point(x, y));
		points.push_back(Point(p1.get_x() + diagonal2 / 2, diagonal1 / 2));
		center.set_x((points[1].get_x() + points[3].get_x()) / 2);
		center.set_y((points[0].get_y() + points[2].get_y()) / 2);
	}
	void scaling(double coefficient) override  {
		double x;
		double y;
		for (size_t i = 0; i < points.size(); i++) {
			x = center.get_x() + (points[i].get_x() - center.get_x())*coefficient;
			y = center.get_y() + (points[i].get_y() - center.get_y())*coefficient;
			points[i].set_x(x);
			points[i].set_y(y);
		}
	}
	ostream& print_shape(ostream& stream, Shape& shape) override {
		stream << "Фигура: ромб" << endl;
		stream << "id фигуры: " << shape.get_id() << endl;
		stream << "Центр фигуры: " << "(" << center.get_x() << ";" << center.get_y() << ")" << endl;
		stream << "Координаты фигуры: " << endl;
		for (size_t i = 0; i < points.size(); i++) {
			stream << "(" << points[i].get_x() << ";" << points[i].get_y() << ")" << endl;
		}
		stream << "Цвет фигуры: " << shape.get_color().get_red() << " " << shape.get_color().get_green() << " " << shape.get_color().get_blue() << endl;
		stream << "_____________________________________" << endl;
		return stream;
	}
};

int main() {
	setlocale(LC_ALL, "Russian");

	Square test1(2, { 255, 255, 255 }, { 1, 2 });
	cout << test1;
	test1.rotation(30);
	cout << test1;
	Parallelogram test2 ({ 128,35,127 }, { 1, 5 }, { -1,9 }, { 7,9 });
	cout << test2;
	test2.scaling(2);
	cout << test2;
	Rhombus test3(7, 3, { 0,0 }, { 123, 23, 77 });
	cout << test3;
	test3.moving({ 3, 6 });
	cout << test3;
	return 0;
}