#include <iostream>
#include <cmath>

struct RGB
{
	int RED;
	int GREEN;
	int BLUE;
};

class Shape
{
protected:
	int cx;
	int cy;
	RGB color;
	int angle;
	static int iam;
public:
	Shape() : cx(0), cy(0), color({0,0,0}), angle(0)
	{ iam++; }

	Shape(int x, int y, RGB c, int a) : cx(x), cy(y), color(c), angle(a)
	{ iam++; }

	virtual void scale(int num) = 0;

	void move(int x, int y)
	{
		this->cx = x;
		this->cy = y;
	}

	void change_angle(int a)
	{

		this->angle += a;

		if (this->angle > 360)
			this->angle %= 360;

		if (this->angle < 0)
			this->angle += 360;

	}

	void set_colors(int a, int b, int c)
	{
		color.RED = a;
		color.GREEN = b;
		color.BLUE = c;
	}

	RGB get_colors()
	{
		return color;
	}

	friend std::ostream& operator<<(std::ostream& out, Shape& sh){
		out << "ID = " << iam << std::endl;
		out << "centre: (" << sh.cx << ", " << sh.cy << ")" << std::endl;
		out << "angle: " << sh.angle << std::endl;
		out << "colors (RGB): " << sh.color.RED << ", " << sh.color.GREEN << ", " << sh.color.BLUE << std::endl;
		out << std::endl;
	}
};

class Triangle : public Shape
{
protected:
	int a;
	int b;
	int c;

public:
	Triangle() : Shape(), a(0), b(0), c(0)
	{}

	Triangle(int cx, int cy, RGB colour, int angle, int a, int b, int c) : Shape(cx, cy, colour, angle), a(a), b(b), c(c)
	{}

	void scale(int num)
	{
		if (num >= 0)
		{
			a *= num;
			b *= num;
			c *= num;
		}
		else
		{
			a /= abs(num);
			b /= abs(num);
			c /= abs(num);
		}

	}

};

class RightTriangle : public Triangle
{
protected:
	std::string name = "RightTriangle";
public:
	RightTriangle() : Triangle()
	{}

	RightTriangle(int cx, int cy, RGB c, int angle, int a, int b) : Triangle(cx, cy, c, angle, a, b, sqrt(pow(a, 2) + pow(b, 2)))
	{}

};

class Star5 : public Shape
{
public:
	int a;
	std::string name = "Five-pointed star";

	Star5() : Shape(), a(0)
	{}

	Star5(int cx, int cy, RGB c, int angle, int a) : Shape(cx, cy, c, angle), a(a)
	{}

	void scale(int num)
	{
		if (num >= 0)
		{
			a *= num;
		}
		else
		{
			a /= abs(num);
		}
	}

};

int Shape::iam = 0;

int main(){

	std::cout << "Triangle --------------------------------------------" << std::endl << std::endl;
	Triangle tr(0, 0, {0, 0, 255}, 45, 10, 20, 30);
	std::cout << tr << std::endl;

	std::cout << "moving... (10, 10)" << std::endl;
	tr.move(10, 10);

        std::cout << "scaling... (-10)" << std::endl;
        tr.scale(-10);

	std::cout << "rotating... (-20)" << std::endl << std::endl;
	tr.change_angle(-20);

	std::cout << tr << std::endl;
	std::cout << "RightTriangle ----------------------------------------" << std::endl << std::endl;

        RightTriangle rtr(100, 2, {255, 0, 255}, 90, 2, 2);
        std::cout << rtr << std::endl;

        std::cout << "moving... (-100, 2)" << std::endl;
        rtr.move(-100, 2);

        std::cout << "scaling... (-2)" << std::endl;
        rtr.scale(-2);

        std::cout << "rotating... (100)" << std::endl << std::endl;
        rtr.change_angle(100);

        std::cout << rtr << std::endl;
	std::cout << "Five-pointed Star -------------------------------------" << std::endl << std::endl;

        Star5 st(5, 5, {255, 255, 255}, 0, 100);
        std::cout << st << std::endl;

        std::cout << "moving... (5, 6)" << std::endl;
        st.move(5, 6);

        std::cout << "scaling... (50)" << std::endl;
        st.scale(50);

        std::cout << "rotating... (100)" << std::endl << std::endl;
        st.change_angle(100);

        std::cout << st << std::endl;

/*
	Triangle tri(0, 0, {1,2,3}, 45, 10, 20, 30), *ptri;
	std::cout << tri;
	RightTriangle rtri(1,1, {1,2,3}, 90, 10, 20), *prtri;
	std::cout << rtri;
	ptri = &rtri;
	std::cout << *ptri;*/
}
