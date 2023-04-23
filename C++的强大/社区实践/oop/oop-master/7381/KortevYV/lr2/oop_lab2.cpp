#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

struct Point {
	double x;
	double y;

	Point(double x,double y):x(x),y(y){}
};

struct Color {
	unsigned char r, g, b;

	Color(char r,char g,char b):r(r),g(g),b(b){}

};

class Shape {
protected:
	Point center;
	int angle;
	Color color;
public:
	Shape(const int angle = 0, const Point center = Point(0, 0), const Color color = Color(0, 0, 0)) :angle(angle), center(center), color(color) { }
	~Shape() {}

	Color get_color() { return color; }
	void change_color(Color color) {
		this->color = color;
	}

	virtual void scale(const double factor) = 0;

	void move(const Point new_center) {
		this->center = new_center;
	}

	void rotate(const int delta) {
		this->angle += delta;

		if (this->angle > 360)
			this->angle %= 360;
		if (this->angle < 0)
			this->angle += 360;
	}
};


class Triangle : public Shape{
protected:
	double a;
	double b;
	double ab_angle;
public:
	Triangle(const double a,const double b,const double ab_angle,const int angle=0,const Point center=Point(0,0),const Color color = Color(0, 0, 0))
		: Shape(angle,center, color) ,a(a),b(b),ab_angle(ab_angle){}
	~Triangle(){}

	void scale(const double factor) override {
		if (factor <= 0) {
			return;
		}
		a *= factor;
		b *= factor;
	}

	friend std::ostream & operator << (std::ostream &out, const Triangle &obj) {
		out << "--------------------" << endl
			<< "Color= (" << int(obj.color.r) << ", " << int(obj.color.g) << ", " << int(obj.color.b) << ")" << endl
			<< "Center= (" << obj.center.x << ", " << obj.center.y << ")" << endl
			<< "Angle= " << obj.angle << endl
			<< "A= " << obj.a << endl
			<< "B= " << obj.b << endl
			<< "AB angle= " << obj.ab_angle << endl
			<< "--------------------" << endl;
		return out;
	}
};

class Sq_Triangle : public Triangle {
public:
	Sq_Triangle(const double a, const double b,const int angle=0,const Point center=Point(0,0), const Color color = Color(0, 0, 0)) : Triangle(a,b,90,angle,center, color) {}
	~Sq_Triangle(){}
};

class Fivepointed_star : public Shape {
protected:
	double edge;
public:
	Fivepointed_star(const double edge,const int angle,const Point center=Point(0,0),const Color color=Color(0,0,0)) : Shape(angle,center,color), edge(edge){}
	~Fivepointed_star(){}

	void scale(const double factor) override{
		if (factor <= 0)
			return;
		edge *= factor;
	}

	friend std::ostream & operator << (std::ostream &out, const Fivepointed_star &obj) {
		out << "--------------------" << endl
			<< "Color= (" << int(obj.color.r) << ", " << int(obj.color.g) << ", " << int(obj.color.b) << ")" << endl
			<< "Center= (" << obj.center.x << ", " << obj.center.y << ")" << endl
			<< "Angle= " << obj.angle << endl
			<< "Stars edge= " << obj.edge << endl
			<< "--------------------" << endl;
		return out;
	}
};

int main()
{
	cout << "Triangle: " << endl;
	Triangle t(10, 20, 30);
	cout << t;
	cout << "Move triangle in (30,20)..." << endl;
	t.move(Point(30, 20));
	cout << "Scale edges in 4..." << endl;
	t.scale(4);
	cout << "Rotate triangle on 30gr.." << endl;
	t.rotate(30);
	cout << "Change triangles color on (254,0,100)" << endl;
	t.change_color(Color(254, 0, 100));
	cout << t;
	cout << "Square Triangle with prev triangles color: " << endl;
	Sq_Triangle sq_t(40, 40, 0, Point(100, 20), t.get_color());
	cout << sq_t;
	cout << "Fivepointed Star: " << endl;
	Fivepointed_star fp_star(10, 20, Point(50, 200), Color(255, 255, 255));
	cout << fp_star;
}

