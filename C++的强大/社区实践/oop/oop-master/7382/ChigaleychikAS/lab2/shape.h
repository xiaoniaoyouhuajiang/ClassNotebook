//
// Created by Alexander on 23.03.2019.
//

#ifndef LAB2_SHAPE_H
#define LAB2_SHAPE_H
#include <cmath>
#include <vector>
#define PI 3.14159265358979323846264338

//triangle trapeze regular pentagon

class Point
{
public:
    Point(int x = 0,int y = 0) :x(x),y(y){};
    Point operator+(const Point &p)
    {
        return Point(this->x+p.x,this->y+p.y);
    }

//private:
    double x;
    double y;
};

struct Color
{
    Color(__int16 a,__int16 b,__int16 c):red(a),green(b),blue(c){}
    __int16 red;
    __int16 green;
    __int16 blue;
};

class Shape
{
public:
    virtual short getId();
    virtual void setColor(Color color);
    virtual Color getColor();
    virtual void move(Point dir);
    virtual void scale(double k); //k for koefficent
    virtual void rotate(int angle); //degress
    virtual Point getAnchor();
    virtual std::vector<Point> getCoordinates();
    //TODO operator cout

    friend std::ostream& operator<<(std::ostream& out, Shape& sh){
		out << "ID = " << sh.id << std::endl;
		out << "colors (RGB): " << sh.color.red << ", " << sh.color.green << ", " << sh.color.blue << std::endl
        << "Coordinates are ";
        for (auto &p : sh.getCoordinates())
        {
            out << p.x <<","<< p.y<<" ";
        }

		out << std::endl;
        return out;
	}
protected:
    Shape():id(setId()),color(Color(0,0,0)),points(){}
    static short setId()
    {
        static short ident = 1;
        return ident++;
    }
    Color color;
    short id;
    std::vector<Point> points;
};

Point Shape::getAnchor()
{
    Point result;
    for (auto x: points)
    {
        result =result + x;
    }
    return result;
}



std::vector<Point> Shape::getCoordinates()
{
    return this->points;
}

void Shape::move(Point dir) {
    for (auto &p : points)
    {
        p = p + dir;
    }
}

void Shape::scale(double k)
{
    Point ancBefore = getAnchor();

    for (auto &p : points)
    {
        p.x *= k;
        p.y *= k;        
    }

    Point ancAfter = getAnchor();
    Point dir = Point (ancBefore.x-ancAfter.x,ancBefore.y-ancAfter.y);
    move(dir);
}

void Shape::rotate(int angle)
{
    double radian = angle * acos(-1) / 180;

    for (auto &p : points) 
    {
        p.x = p.x * cos(radian) - p.y*sin(radian);
        p.y = p.x * sin(radian) + p.y*cos(radian);
    }
}

void Shape::setColor(Color c)
{
    this->color = c;
}

Color Shape::getColor()
{
    return this->color;
}

short Shape::getId()
{
    return this->id;
}

class Triangle : public Shape
{
    public:
    Triangle(Point a, Point b, Point c)
    {
        points.push_back(a);
        points.push_back(b);
        points.push_back(c);
    }

};

class Trapeze : public Shape
{
    public:
    Trapeze(Point a, Point b, Point c, Point d)
    {
        points.push_back(a);
        points.push_back(b);
        points.push_back(c);
        points.push_back(d);
    }
};

class RegPentagon : public Shape 
{
    public:
    RegPentagon(Point a, int edge)
    {
        Point tmp; 
        tmp.x = edge*sin(54*PI/180);
        tmp.y = edge*cos(54*PI/180);


        Point b(a.x+tmp.x,a.y+tmp.y);
        Point e(a.x-tmp.x,a.y+tmp.y);
        
        tmp.x = edge*sin(18*PI/180);
        tmp.y = edge*cos(18*PI/180);

        Point c(b.x - tmp.x,b.y+tmp.y);
        Point d(e.x + tmp.x,e.y+tmp.y);

        points.push_back(a);
        points.push_back(b);
        points.push_back(c);
        points.push_back(d);
        points.push_back(e);
    }
};
#endif //LAB2_SHAPE_H
