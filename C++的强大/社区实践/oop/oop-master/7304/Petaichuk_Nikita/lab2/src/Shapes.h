#pragma once

#include <iostream>
#include "RadiusVector.h"
#include "Color.h"

using namespace std;

//Абстрактный класс фигуры
class Shape
{
public:
    Shape(RadiusVector center, Color color);
    virtual ~Shape();

    void changeColor(Color color);
    void changeColor(unsigned int red, unsigned int green, unsigned int blue);

    Color getColor() const;
    RadiusVector getCenterCoordinates() const;
    unsigned int getID() const;

    virtual void move(RadiusVector destination) = 0;
    virtual void scale(double coefficient) = 0;
    virtual void rotate(double angle) = 0;

protected:
    RadiusVector center;
    Color color;
    unsigned int id;
    static unsigned int next_id;
};

//Класс круга
class Circle : public Shape
{
public:
    Circle(RadiusVector center, Color color, double radius);
    Circle(const Circle &other);
    Circle& operator=(const Circle &other);
    ~Circle();

    void move(RadiusVector destination);
    void scale(double coefficient);
    void rotate(double angle);

    double getRadius() const;

    friend ostream& operator<<(ostream &os, const Circle &circle);
    
private:
    double radius;
};

//Класс ромба
class Rombus : public Shape
{
public:
    Rombus(RadiusVector center, Color color, double side_size, double angle);
    Rombus(const Rombus &other);
    Rombus& operator=(const Rombus &other);
    ~Rombus();

    void move(RadiusVector destination);
    void scale(double coefficient);
    void rotate(double angle);
    void printVertexCoordinates();

    double getSideSize() const;
    double getAngle() const;

    friend ostream& operator<<(ostream &os, const Rombus &rombus);

private:
    RadiusVector left_vertex;
    RadiusVector right_vertex;
    RadiusVector upper_vertex;
    RadiusVector lower_vertex;
    double side_size;
    double angle;
};

//Класс трапеции
class Trapezium : public Shape
{
public:
    Trapezium(RadiusVector upper_base_center, RadiusVector lower_base_center, Color color,
              double upper_base_size, double lower_base_size);
    Trapezium(const Trapezium &other);
    Trapezium& operator=(const Trapezium &other);
    ~Trapezium();

    void move(RadiusVector destination);
    void scale(double coefficient);
    void rotate(double angle);
    void printVertexCoordinates();

    double getUpperBaseSize() const;    
    double getLowerBaseSize() const;
    double getHeight() const;

    friend ostream& operator<<(ostream &os, const Trapezium &trapezium);

private:
    RadiusVector left_upper_vertex;
    RadiusVector right_upper_vertex;
    RadiusVector left_lower_vertex;
    RadiusVector right_lower_vertex;
    double upper_base_size;
    double lower_base_size;
    double height;
};

//Перегрузка операторов << для каждой фигуры



