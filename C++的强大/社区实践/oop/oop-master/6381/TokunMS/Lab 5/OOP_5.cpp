#include <iostream>
#include <cmath>
#include <ctime>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>

using namespace std;

#define NumberOfShapes 10
#define ValueRange 50
	
vector<string> colors {"transparent", "red", "yellow", "blue", "white", "black"};

class Point
{
public:
	float x;
	float y;

	Point(float x_, float y_) : x(x_), y(y_) {};

	void move(float x_, float y_)
	{
		x += x_;
		y += y_;
	};

	void rotate(float alpha)
	{
	 	float x_ = x * cos(alpha) - y * sin(alpha);
	 	float y_ = x * sin(alpha) + y * cos(alpha);
	 	x = x_; y = y_;		
	};

	void scale(Point point0, float k)
	{
		x = point0.x + abs(x - point0.x)*k;
		y = point0.y + abs(y - point0.y)*k;		
	};
};
 
class Shape
{
private:
	unsigned color;	
protected:
	vector<Point> point;
public:
	virtual ~Shape() {};
	virtual void Scale(float k) = 0;
	virtual ostream& put(ostream& out) const = 0;
	friend ostream& operator<< (ostream& s, const Shape& shape_)
	{
		return shape_.put(s);
	}
	virtual float Perimeter() = 0;

	Shape() : color(0) {};

    bool GetX()
    {
        bool found = false;
        for (Point &point_ : point) if(point_.x < 5) found = true;
        return found;
    }

    int GetY()
    {
        bool found = false;
        for (Point &point_ : point) if(point_.y < 5) found = true;
        return found;
    }

	void Move(float x_, float y_)
	{
		for (Point &point_ : point) point_.move(x_, y_);
	}

	void Rotate(float alpha)
	{
		for (Point &point_ : point) point_.rotate(alpha);
	}

	void setColor(unsigned color_)
	{
		if (color_ > colors.size()) throw invalid_argument("It's not such color!");
		color = color_;
	}

	unsigned getColor() const
	{
		return color;
	}
};

class Ellipse : public Shape
{
private:
	float r1;
	float r2;
public:
	Ellipse(Point center, float r1_, float r2_) : r1(r1_), r2(r2_)
	{
		if ((r1_ <= 0) || (r2_ <= 0)) throw invalid_argument("Radius must be positive");
		point.push_back(center);	
	}	

	void Scale(float k) 
	{
		if (k <= 0) throw invalid_argument("Coefficient of scale must be positive");
		r1 *= k;
		r2 *= k;
	}

	float Perimeter() 
	{
		return (3.1416*r1*r2 + abs(r1-r2))/(r1 + r2);
	}
	ostream& put(ostream& out) const
	{
		out << "The figure is ellipse\nwith center in coordinates\n("
			<< point[0].x << "; " << point[0].y << ")\n"
			<< "and radius are r1 = " << r1 << "   r2 = " << r2 << "\n"
			<< "color is " << colors[getColor()] << "\n\n";
		return out;
	}
};

class Trapezium : public Shape
{
private:	
	virtual string FriendlyName() const
	{
		return " ";
	}
protected:
	float topBase;
	float bottomBase;
public:
	Trapezium(Point topLeftCoord, Point bottomLeftCoord, float topBase_, float bottomBase_) : topBase(abs(topBase_)), bottomBase(abs(bottomBase_))
	{
		if ((topLeftCoord.x == bottomLeftCoord.x) && (topLeftCoord.y == bottomLeftCoord.y)) throw invalid_argument("There is not distance between coordinates of left side of trapezium");
		if ((topBase_ <= 0) || (bottomBase_ <= 0)) throw invalid_argument("Bases of trapezium must be positive");
		
		point.push_back(topLeftCoord);
		point.push_back(bottomLeftCoord);
		point.push_back(Point(topLeftCoord.x + topBase, topLeftCoord.y));
		point.push_back(Point(bottomLeftCoord.x + bottomBase, bottomLeftCoord.y));
    }

	void Scale(float k)   
	{
		if (k <= 0) throw invalid_argument("Coefficient of scale must be positive");
		for (int i = 1; i < point.size(); i++) point[i].scale(point[0], k);
		topBase *= k; bottomBase *= k;
	}

	float Distance(Point a, Point b)
	{
		return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
	}

	float Perimeter()
	{
		float p = 0;
		for (int i = 0; i < point.size() - 2; i++) p += Distance(point[i], point[i+1]);
		p += Distance(point[0], point[point.size()-1]);
		return p;
	}

	ostream& put(ostream& out) const
	{
		out << "The figure is" << FriendlyName() << "trapezium\nwith coordinates\n";
		for (int i = 0; i < point.size(); i++) out << "(" << point[i].x << "; " << point[i].y << ")\n";
		out << "length of basis are top_base = " << topBase << "   bottom_base = " << bottomBase
			<< "\ncolor is " << colors[getColor()] << "\n\n";
		return out;
	}
};

class IsoscelesTrapezium : public Shape
{
protected:
	float topBase;
	float bottomBase;
private:
	virtual string FriendlyName() const
	{
		return " isolated ";
	}
public:
	IsoscelesTrapezium(Point topLeftCoord, Point bottomLeftCoord, float topBase_, float bottomBase_) : topBase(topBase_), bottomBase(bottomBase_)
	{
        topBase_ = abs(-2 * topLeftCoord.x + bottomBase + 2 * bottomLeftCoord.x);
		if ((topLeftCoord.x == bottomLeftCoord.x) && (topLeftCoord.y == bottomLeftCoord.y)) throw invalid_argument("There is not distance between coordinates of left side of isotrapezium");
		if ((topBase_ <= 0) || (bottomBase_ <= 0)) throw invalid_argument("Bases of isotrapezium must be positive");
		
		point.push_back(topLeftCoord);
		point.push_back(bottomLeftCoord);
		point.push_back(Point(topLeftCoord.x + topBase, topLeftCoord.y));
		point.push_back(Point(bottomLeftCoord.x + bottomBase, bottomLeftCoord.y));
	}

    ostream& put(ostream& out) const
	{
		out << "The figure is" << FriendlyName() << "trapezium\nwith coordinates\n";
		for (int i = 0; i < point.size(); i++) out << "(" << point[i].x << "; " << point[i].y << ")\n";
		out << "length of basis are top_base = " << topBase << "   bottom_base = " << bottomBase
			<< "\ncolor is " << colors[getColor()] << "\n\n";
		return out;
	}

    void Scale(float k)   
	{
		if (k <= 0)
			throw invalid_argument("Coefficient of scale must be positive");
		for (int i = 1; i < point.size(); i++) point[i].scale(point[0], k);
		topBase *= k; bottomBase *= k;
	}

    float Distance(Point a, Point b)
	{
		return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
	}

    float Perimeter()
	{
		float p = 0;
		for (int i = 0; i < point.size() - 2; i++) p += Distance(point[i], point[i+1]);
		p += Distance(point[0], point[point.size()-1]);
		return p;
	}
};

void GenerateShapes(vector<shared_ptr<Shape> >& Shapes)
{
	srand(time(nullptr));
	for (shared_ptr<Shape> &shape : Shapes)
	{
		int object = rand() % 3;
		switch (object) 
		{
			case 0:
            {
				shape.reset(new Ellipse({ abs((float) (rand() % 20 + 1)),  abs((float) (rand() %20 + 1)) }, abs(rand() % ValueRange) + 1, abs(rand() % ValueRange) + 1));
				break;
			}
			case 1:
            {
				shape.reset(new Trapezium({ abs((float)(rand() % 20 + 1)),  abs((float)(rand() % 20 + 1)) }, { abs((float) (rand() % 20 + 1)),  abs((float) (rand() % 20 + 1)) }, abs((float)(rand() % ValueRange) + 1), abs((float)(rand() % ValueRange) + 1)));
				break;
			}
			case 2:
            {
				shape.reset(new IsoscelesTrapezium({ abs((float) (rand() % 20 + 1)),  abs((float) (rand() %20 + 1)) }, { abs((float) (rand() % 20 + 1)),  abs((float) (rand() %20 + 1)) }, abs((float)(rand() % ValueRange) + 1), abs((float)(rand() % ValueRange) + 1)));
				break;
			}
		}
	}
}

int main()
{
	vector<shared_ptr<Shape>> shapes(NumberOfShapes);
	GenerateShapes(shapes);
	
	cout << "Result of searching for elements:" << endl;
	for (shared_ptr<Shape> &shape : shapes) if (!(*shape).GetX() && !(*shape).GetY()) cout << *shape << endl;
	
	cout << "***********************************************" << endl;
	cout << "Deleted elements: " << endl;
	for(int i = 0, iterator = 0; i < NumberOfShapes; i++)
	{
		shared_ptr<Shape> &shape = shapes[i - iterator];
		if(!(*shape).GetX() && !(*shape).GetY())
		{
			shapes.erase(shapes.begin() + i - iterator);
			cout << "Deleted element number " << i+1 << endl;
			iterator++;
		}
	}
	cout << "***********************************************" << endl;
	cout << "Ramaining elements:" << endl;
	for (shared_ptr<Shape> &shape : shapes)	cout << *shape << endl;
	
	return 0;
}