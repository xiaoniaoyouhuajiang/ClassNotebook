#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <cmath>
#include <string>
#include <vector>

#define PI 3.14159

class Point{
public:
    int x, y;
public:
    Point(int x = 0, int y = 0): x(x), y(y){}
    friend std::ostream& operator<<(std::ostream&, const Point&);
    friend class Parallelogram;
    Point& operator=(Point& point){this->x = point.x; this->y = point.y; return *this;}
};

class Shape{
protected:
    static unsigned id;
    static std::string defaultColor;
    Point centre;
    unsigned D1, D2;
    std::string color;
    double angle;
public:
    void rotate(double newAngle){angle += newAngle;}
    void multiplicateCoordinate(unsigned k){D1*=k; D2*=k;}
    void changeCoordinate(Point newCentre){centre = newCentre;}
    void setColor(std::string newColor){color = newColor;}
    virtual double calculatePerimeter() = 0;
    virtual double calculateArea() = 0;
    virtual void print() = 0;
    friend std::ostream& operator<<(std::ostream&, const Shape&);
};

class Parallelogram: public Shape{
    unsigned id;
    double parAngle;
public:
    Parallelogram(Point centre, unsigned D1, unsigned D2, std::string color, double newParAngle){
        angle = 0; // default angle
        id = Shape::id;
        this->centre = centre;
        this->D1 = D1;
        this->D2 = D2;
        this->color = color;
        parAngle = newParAngle;
    }
    void print() override{std::cout << *this;}
    double calculatePerimeter();
    double calculateArea();
    friend std::ostream& operator<<(std::ostream&, const Parallelogram&);
};

class Ellipse: public Shape{
    unsigned id;
public:
    Ellipse(Point centre, unsigned D1, unsigned D2, std::string color){ // инициализация через ":" ?
        angle = 0; // default angle
        id = Shape::id;
        this->centre = centre;
        this->D1 = D1;
        this->D2 = D2;
        this->color = color;
    }
    void print() override{std::cout << *this;}
    double calculatePerimeter();
    double calculateArea();
    friend std::ostream& operator<<(std::ostream&, const Ellipse&);
};

class EllipseSector: public Ellipse{
    unsigned id;
    double sectorAngle;
public:
    EllipseSector(Point centre, unsigned D1, unsigned D2, std::string color, double newSectorAngle):
        Ellipse(centre, D1, D2, color), sectorAngle(newSectorAngle){
       id = Shape::id;
    }
    void print() override{std::cout << *this;}
    double calculatePerimeter();
    double calculateArea();
    friend std::ostream& operator<<(std::ostream&, const EllipseSector&);
};

#endif // SHAPE_H
