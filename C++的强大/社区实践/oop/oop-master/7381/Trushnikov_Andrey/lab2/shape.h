#include <iostream>
#include <vector>
#include <cmath>
#ifndef SHAPE_H
#define SHAPE_H

class Point{
    double x,y;
public:
    Point(double,double);
    void rotate_p(double, Point);
    void setX(double);
    void setY(double);
    double getX();
    double getY();
    friend std::ostream& operator<<(std::ostream& out,Point point);

};

class Colour{
    int r,g,b;
public:
    Colour(){}
    Colour(int, int,int);
    void setRed(int);
    void setGreen(int);
    void setBlue(int);
    int getRed();
    int getGreen();
    int getBlue();
    friend std::ostream& operator<<(std::ostream& out, Colour color);
};

class Shape{
protected:
    std::vector <Point> coord;
    Colour colour;
    unsigned long long id;
    static unsigned  long long counter;

public:
    Shape(){
        id=counter++;
    }
    void move(Point);
    void rotate(double);
    virtual void scale(double) = 0;
    virtual double perimetr() = 0;
    virtual double area() = 0;
    virtual void print(std::ostream&) = 0;
    virtual ~Shape(){}
    void setColour(Colour);
    void setPoints(std::vector <Point>);
};

#endif // SHAPE_H
